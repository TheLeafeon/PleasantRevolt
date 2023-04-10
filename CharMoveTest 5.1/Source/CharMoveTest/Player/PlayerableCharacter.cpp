// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerableCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "CharMoveTest/Interaction/HandUP.h"

// Sets default values
APlayerableCharacter::APlayerableCharacter() : LadderMoveSpeed(3.0f), SaveZLocation(0.0f), StopLadderMove(false), isLeftLadder(false), SaveValue(0), SaveValue2(0), isTopDown(false), isLeftRight(false)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Player Rolling Curve
	static ConstructorHelpers::FObjectFinder<UCurveFloat> RollCurveObj(TEXT("/Game/PlayerTest/Player/Curves/RollingCurve"));
	if (RollCurveObj.Succeeded())
	{
		RollCurve = RollCurveObj.Object;
	}

	// Timer 남은 시간 확인용
	RemainingTime = 0.0f;

	// Player Status
	Player_HP = 4.0f;
	Player_Roll_Time = 600.0f;

	// Player Dodge
	Player_Dodge_Time = 1.0f;
	isDodge = false;

	// Player Melee
	bisAttack = false;
	currentCombo = 0;
	maxCombo = 0;
	comboCoolTime = 5.0f;
	// Interaction System
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction box"));
	InteractionBox->SetupAttachment(RootComponent);

	Interface = nullptr;
	WeaponInterface = nullptr;
}

// Called to bind functionality to input
void APlayerableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerableCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerableCharacter::MoveRight);

	PlayerInputComponent->BindAction("Rolling", IE_Released, this, &APlayerableCharacter::Rolling);

	PlayerInputComponent->BindAction("Interact", IE_Released, this, &APlayerableCharacter::OnInteract);

	// 근거리 관련 입력
	PlayerInputComponent->BindAction("FirstMeleeWeapon", IE_Released, this, &APlayerableCharacter::FirstMeleeWeapon);
	PlayerInputComponent->BindAction("SecondMeleeWeapon", IE_Released, this, &APlayerableCharacter::SecondMeleeWeapon);
	PlayerInputComponent->BindAction("MeleeAttack", IE_Pressed, this, &APlayerableCharacter::Attack_Melee);
	
	PlayerInputComponent->BindAction("ShootingAttack", IE_Released, this, &APlayerableCharacter::Attack_Shooting);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("TurnRate", this, &APlayerableCharacter::TurnAtRate);
	//PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerableCharacter::LookUpAtRate);
}

void APlayerableCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerableCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerableCharacter::MoveForward(float Value)
{
	SaveValue = Value;
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		if (isLadder && isTopDown)
		{
			if (isLeftLadder)
			{
				LadderLeftMove(Value);
			}
			else
			{
				LadderRightMove(Value);
			}
			
		}
		else
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

void APlayerableCharacter::MoveRight(float Value)
{
	SaveValue2 = Value;

	if ((Controller != nullptr) && (Value != 0.0f))
	{
		if (isLadder && isLeftRight)
		{
			if (isLeftLadder)
			{
				LadderLeftMove(Value);
			}
			else
			{
				LadderRightMove(Value);
			}
		}
		else
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		}
	}
}

void APlayerableCharacter::TimelineProgress(float Value)
{
	// Interpolate between the start and end rotations based on the current value of the timeline
	FRotator NewRotation = FMath::Lerp(StartRotation, EndRotation, Value);

	if (Value >= 1.0f)
	{
		bIsRolling = false;
	}

	// Set the rotation of your character to the interpolated value
	SetActorRotation(NewRotation);

}

void APlayerableCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->bShowMouseCursor = true;

	AnimInstance = Cast<UPlayerAnimInstnce>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance)
		return;
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("NotReturn"));

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	CurrentWeapon = GetWorld()->SpawnActor<AWeaponBase>(FirstWeapon, SpawnParams);
	if (CurrentWeapon)
	{
		MeleeWeaponsArray.Add(CurrentWeapon);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("WeaponSocket_r"));
		CurrentWeaponComboAnim = AnimInstance->NearWeapon1_AnimMontage;
		maxCombo = CurrentWeapon->GetMaxCombo();

		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("NearWeapon1"));
	}
	if (AWeaponBase* Weapon = GetWorld()->SpawnActor<AWeaponBase>(SecondWeapon, SpawnParams))
	{
		Weapon->GetWeponMesh()->SetHiddenInGame(true);
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("WeaponSocket_r"));
		MeleeWeaponsArray.Add(Weapon);
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("NearWeapon2"));
	}

	// initialize the timeline and the curve float
	RollTimeline.SetLooping(false);
	RollTimeline.SetTimelineLength(RollAnimationLength);
	RollTimeline.SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);
	// 상호작용용 박스관련 Dynamic에 추가
	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerableCharacter::OnBoxBeginOverlap);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &APlayerableCharacter::OnBoxEndOverlap);
}

void APlayerableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->GetTimerManager().IsTimerActive(RollTimerHandle))
	{
		RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(RollTimerHandle);
		if (RemainingTime <= 0.0f)
		{
			EnableInputAfterRoll();
		}
	}
	if (GetWorld()->GetTimerManager().IsTimerActive(DodgeTimerHandle))
	{
		RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(DodgeTimerHandle);
		if (RemainingTime <= 0.0f)
		{
			DodgeEnd();
		}
	}
	if (GetWorld()->GetTimerManager().IsTimerActive(NextComboTimerHandle))
	{
		RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(NextComboTimerHandle);
		if (RemainingTime <= 0.0f)
		{
			Attack_Melee_End();
		}
	}
	if (GetWorld()->GetTimerManager().IsTimerActive(DeathTimerHandle))
	{
		RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(DeathTimerHandle);
		if (RemainingTime <= 0.0f)
		{
			DeathEnd();
		}
	}
}

//=============== Test Player HP =============== //
float APlayerableCharacter::Get_Player_HP()
{
	return Player_HP;
}

void APlayerableCharacter::Increase_Player_HP(float val)
{
	Player_HP += val;
}

//===============  Player Dodge =============== //
void APlayerableCharacter::DodgeStart(const float& time)
{
	if (!isDodge)
	{
		isDodge = true;

		GetWorld()->GetTimerManager().SetTimer(DodgeTimerHandle, this, &APlayerableCharacter::DodgeEnd, time, false);
	}
}

void APlayerableCharacter::DodgeEnd()
{
	isDodge = false;
}

//=============== player get Damage =============== //

void APlayerableCharacter::OnHit(float DamageTaken, FDamageEvent const& DamgaeEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	AnimInstance->PlayBeHitMontage();

	if (DamageTaken > 0.f)
	{
		ApplyDamageMomentum(DamageTaken, DamgaeEvent, PawnInstigator, DamageCauser);
	}
}

float APlayerableCharacter::TakeDamage(float Damage, FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float getDamage = Super::TakeDamage(Damage, DamgaeEvent, EventInstigator, DamageCauser);

	if (!isDodge)
	{
		if (Player_HP <= 0.0f)
			return 0.0f;

		if (getDamage > 0.f)
		{
			Player_HP -= getDamage;
		}

		if (Player_HP <= 0)
		{
			Die(getDamage, DamgaeEvent, EventInstigator, DamageCauser);
		}
		else
		{
			OnHit(getDamage, DamgaeEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
			DodgeStart(Player_Dodge_Time);
		}
	}

	return getDamage;
}

void APlayerableCharacter::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	Player_HP = FMath::Min(0.f, Player_HP);

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();

	Killer = GetDamageInstigator(Killer, *DamageType);
	/*
	GetWorldTimerManager().ClearAllTimersForObject(this);

	if (Controller != NULL)
	{
		Controller->UnPossess();
	}
*/
	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}

	float DeathAnimDuration = PlayAnimMontage(AnimInstance->Death_AnimMontage);

	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &APlayerableCharacter::DeathEnd, DeathAnimDuration, false);
}

void APlayerableCharacter::DeathEnd()
{
	//this->SetActorHiddenInGame(this);
	SetLifeSpan(0.1f);
}

//=============== Weapon & Switching System =============== //

void APlayerableCharacter::SwitchWeapon(int32 WeaponIndex)
{
	if (CurrentWeapon)
	{
		if (MeleeWeaponsArray[WeaponIndex] == NULL)
			return;
		
		AWeaponBase* NextWeapon = MeleeWeaponsArray[WeaponIndex];

		CurrentWeapon->GetWeponMesh()->SetHiddenInGame(true);
		CurrentWeapon = NextWeapon;
		CurrentWeapon->GetWeponMesh()->SetHiddenInGame(false);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Change to NearWeapon %d"), WeaponIndex));


		if (WeaponIndex == FIRST_WEAPON)
		{
			CurrentWeaponComboAnim = AnimInstance->NearWeapon1_AnimMontage;
		}
		else if (WeaponIndex == SECOND_WEAPON)
		{
			CurrentWeaponComboAnim = AnimInstance->NearWeapon2_AnimMontage;
		}

		maxCombo = CurrentWeapon->GetMaxCombo();
		currentCombo = 0;
	}
}

void APlayerableCharacter::FirstMeleeWeapon()
{
	SwitchWeapon(FIRST_WEAPON);
}

void APlayerableCharacter::SecondMeleeWeapon()
{
	SwitchWeapon(SECOND_WEAPON);
}

//===============  Player Melee Attack =============== //

void APlayerableCharacter::Attack_Melee()
{
	if (!bisAttack)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %d"), currentCombo));

		if (currentCombo < maxCombo)
		{
			FString PlayerSection = "Attack_" + FString::FromInt(currentCombo);
			PlayAnimMontage(CurrentWeaponComboAnim, 1.0f, FName(*PlayerSection));
			currentCombo++;
			bisAttack = true;
			GetWorld()->GetTimerManager().SetTimer(NextComboTimerHandle, this, &APlayerableCharacter::Attack_Melee_End, comboCoolTime, false);
		}
		else
		{
			Attack_Melee_End();
		}
	}
}

void APlayerableCharacter::Enable_Attack_Enemy()
{
	WeaponInterface = Cast<IWeaponInterface>(CurrentWeapon);

	if (WeaponInterface)
	{
		WeaponInterface->Enable_Attack_Enemy();
	}
}

void APlayerableCharacter::Disable_Attack_Enemy()
{
	WeaponInterface = Cast<IWeaponInterface>(CurrentWeapon);

	if (WeaponInterface)
	{
		WeaponInterface->Disable_Attack_Enemy();
	}
}

void APlayerableCharacter::Attack_Melee_End()
{
	currentCombo = 0;
	bisAttack = false;
}

void APlayerableCharacter::Attack_Shooting()
{
}

//=============== Player Roll =============== //
// 추후 문제 시 수정
float APlayerableCharacter::UpdateRollCurve(float Value)
{
	FRotator RollRotation = FRotator{ 0.0f, 0.0f, Value * 360.0f };
	SetActorRotation(RollRotation);

	if (Value >= 1.0f)
	{
		bIsRolling = false;
	}

	return RollRotation.NormalizeAxis(0.0f);
}

void APlayerableCharacter::EnableInputAfterRoll()
{
	//GetCharacterMovement()->StopMovementImmediately();
	//GetCharacterMovement()->Velocity = FVector::ZeroVector;
	// Re-enable input after rolling
	//PlayerController->SetInputMode(FInputModeGameOnly());

	//PlayerController->EnableInput(PlayerController);
	//PlayerController->FlushPressedKeys();
	bIsRolling = false;
}

void APlayerableCharacter::Rolling()
{
	if (bIsRolling || (GetCharacterMovement()->IsFalling()) || GetCharacterMovement()->Velocity == FVector::ZeroVector)
	{
		return;
	}

	bIsRolling = true;
	/*
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->DisableInput(PlayerController);

	RollTimeline = FTimeline{};
	FOnTimelineFloat RollCurveUpdate;

	//RollTimeline.AddInterpFloat(RollCurve, FOnTimelineFloat::CreateUObject(this, &APlayerableCharacter::TimelineProgress));
	
	RollCurveUpdate.BindUFunction(this, "TimelineProgress");
	RollTimeline.AddInterpFloat(RollCurve, RollCurveUpdate);

	StartRotation = GetActorRotation();
	EndRotation = GetActorRotation() + FRotator(0.0f, 90.0f, 0.0f);

	RollCurveUpdate.BindUFunction(this, "UpdateRollCurve");
	RollTimeline.AddInterpFloat(RollCurve, RollCurveUpdate);

	FVector RollDirection = GetActorForwardVector().RotateAngleAxis(UpdateRollCurve(RollTimeline.GetPlaybackPosition()), FVector{ 0.0f, 0.0f, 1.0f });
	
	GetCharacterMovement()->Velocity = RollDirection;

	RollTimeline.PlayFromStart();
	*/
	AnimInstance->PlayRollingMontage();
	float timer = AnimInstance->Rolling_AnimMontage->GetPlayLength();

	GetWorld()->GetTimerManager().SetTimer(RollTimerHandle, this, &APlayerableCharacter::EnableInputAfterRoll, timer, false);
	DodgeStart(timer);
}

void APlayerableCharacter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Interface = Cast<IInteractionInterface>(OtherActor);

	if (Interface)
	{
		Interface->ShowInteractionWidget();
	}
}

void APlayerableCharacter::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Interface)
	{
		Interface->HideInteractionWidget();
		Interface = nullptr;
	}
}

void APlayerableCharacter::OnInteract()
{
	if (Interface)
	{
		Interface->InteractWithMe();
	}
}
void APlayerableCharacter::PlayerHandUp(AActor* OtherActor)
{
	if (OtherActor)
	{
		OtherActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("handUp"));
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("PlayerHandUp"));
	}

}

void APlayerableCharacter::LadderRightMove(float Value)
{
	if (Value > 0)
	{
		if (!StopLadderMove)
		{
			AnimInstance->PlayLadderMoveUpMontage();
			StopLadderMove = true;
		}

		SetActorLocation(GetActorLocation() + FVector(0, 0, LadderMoveSpeed));
	}
	else if (Value < 0)
	{
		if (GetActorLocation().Z <= SaveZLocation)
		{
			SetLadderMoveFalse();
		}
		else if (!StopLadderMove)
		{
			AnimInstance->PlayLadderMoveDownMontage();
			StopLadderMove = true;
		}

		SetActorLocation(GetActorLocation() + FVector(0, 0, LadderMoveSpeed * -1));
	}
}

void APlayerableCharacter::LadderLeftMove(float Value)
{
	if (Value < 0)
	{
		if (!StopLadderMove)
		{
			AnimInstance->PlayLadderMoveUpMontage();
			StopLadderMove = true;
		}

		SetActorLocation(GetActorLocation() + FVector(0, 0, LadderMoveSpeed));
	}
	else if (Value > 0)
	{
		if (GetActorLocation().Z <= SaveZLocation)
		{
			SetLadderMoveFalse();
		}
		else if (!StopLadderMove)
		{
			AnimInstance->PlayLadderMoveDownMontage();
			StopLadderMove = true;
		}

		SetActorLocation(GetActorLocation() + FVector(0, 0, LadderMoveSpeed * -1));
	}

}

//아래 두 개는 사다리 블루프린트에서 호출
void APlayerableCharacter::SetLadderMoveTrue()
{
	//사다리 모드
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("1 ") + FString::SanitizeFloat(SaveValue)); //이건 안 건들였을 때 0
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("2 ") + FString::SanitizeFloat(SaveValue2));

	if (SaveValue > 0 && SaveValue2 == 0)
	{
		isLeftLadder = false;
		isTopDown = true;
	}
	else if (SaveValue2 > 0 && SaveValue == 0)
	{
		isLeftLadder = false;
		isLeftRight = true;
	}
	else if (SaveValue < 0 && SaveValue2 == 0)
	{
		isLeftLadder = true;
		isTopDown = true;
	}
	else if (SaveValue2 < 0 && SaveValue == 0)
	{
		isLeftLadder = true;
		isLeftRight = true;
	}
	else if (SaveValue > 0 && SaveValue2 > 0)
	{
		//키 하나만 받게 하기
		isLeftLadder = false; //오른쪽 위
		isTopDown = true;
		//위 기준
	}
	else if (SaveValue < 0 && SaveValue2 > 0) //오른쪽 아래
	{
		isLeftLadder = false;
		isLeftRight = true;
		//오른쪽 기준으로 하게 하기
	}
	else if (SaveValue > 0 && SaveValue2 < 0)
	{
		isLeftLadder = true; //왼쪽 위
		isLeftRight = true;
		//왼쪽 기준으로 하게 하기
	}
	else if (SaveValue < 0 && SaveValue2 < 0) //왼쪽 아래
	{
		isLeftLadder = true;
		isTopDown = true;
		//아래 기준
	}

	isLadder = true;
	//이때 로케이션을 저장해두고 로케이션 Z축 이하게 되면 강제로 원래 로케이션으로 돌리고 False호출
	SaveZLocation = GetActorLocation().Z;
}

void APlayerableCharacter::SetLadderMoveFalse()
{
	//사다리 끝
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("MoveFalse"));
	AnimInstance->StopLadderMoveMontage();
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	isLadder = false;
	StopLadderMove = false;
	isTopDown = false;
	isLeftRight = false;
}