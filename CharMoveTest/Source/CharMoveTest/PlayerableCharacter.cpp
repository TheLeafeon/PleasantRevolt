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

// Sets default values
APlayerableCharacter::APlayerableCharacter()
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

	// Player Status
	Player_HP = 4.0f;
	Player_Speed = 0.0f;
	Player_Roll_Test = 600.0f;
	Player_Attack_Power = 0.0f;
	Player_Attack_Near_Distance = 0.0f;
	Player_Attack_Far_Distance = 0.0f;

	// Player Melee
	isAttack = false;

	// Interaction System
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction box"));
	InteractionBox->SetupAttachment(RootComponent);

	Interface = nullptr;
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

	PlayerInputComponent->BindAction("MeleeAttack", IE_Released, this, &APlayerableCharacter::Attack_Melee);
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
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerableCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
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

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->bShowMouseCursor = true;

	AnimInstance = Cast<UPlayerAnimInstnce>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance)
		return;
	
	// initialize the timeline and the curve float
	RollTimeline.SetLooping(false);
	RollTimeline.SetTimelineLength(RollAnimationLength);
	RollTimeline.SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerableCharacter::OnBoxBeginOverlap);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &APlayerableCharacter::OnBoxEndOverlap);
}

void APlayerableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
	{
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(TimerHandle);
		if (RemainingTime <= 0.0f)
		{
			EnableInputAfterRoll();
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

//=============== Melee Attack =============== //

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

	GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerableCharacter::DeathEnd, DeathAnimDuration, false);
}

void APlayerableCharacter::DeathEnd()
{
	//this->SetActorHiddenInGame(this);
	SetLifeSpan(0.1f);
}

void APlayerableCharacter::Attack_Melee()
{
	if (!isAttack)
	{
		AnimInstance->PlayMeleeAttackMontage();

		//isAttack = true;
	}
}

void APlayerableCharacter::Attack_Melee_End()
{
	isAttack = false;
}

void APlayerableCharacter::Attack_Shooting()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Shooting"));
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
	GetCharacterMovement()->StopMovementImmediately();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	/*
	PlayerController->InputComponent->ClearBindingValues();
	PlayerController->InputComponent->ClearActionBindings();
	PlayerController->InputComponent->AxisBindings.Empty();
*/
	GetCharacterMovement()->Velocity = FVector::ZeroVector;
	// Re-enable input after rolling
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->EnableInput(PlayerController);
	PlayerController->FlushPressedKeys();
	bIsRolling = false;
}

void APlayerableCharacter::Rolling()
{
	if (bIsRolling || (GetCharacterMovement()->IsFalling()))
	{
		return;
	}

	bIsRolling = true;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetInputMode(FInputModeUIOnly());
	//PlayerController->bShowMouseCursor = true;
	PlayerController->DisableInput(PlayerController);

	AnimInstance->PlaySampleMontage();

	RollTimeline = FTimeline{};
	FOnTimelineFloat RollCurveUpdate;

	// Bind the timeline to the function that will be called when it is updated
	//RollTimeline.AddInterpFloat(RollCurve, FOnTimelineFloat::CreateUObject(this, &APlayerableCharacter::TimelineProgress));
	
	RollCurveUpdate.BindUFunction(this, "TimelineProgress");
	RollTimeline.AddInterpFloat(RollCurve, RollCurveUpdate);

	// Set the start and end rotations for the roll animation
	StartRotation = GetActorRotation();
	EndRotation = GetActorRotation() + FRotator(0.0f, 90.0f, 0.0f);

	RollCurveUpdate.BindUFunction(this, "UpdateRollCurve");
	RollTimeline.AddInterpFloat(RollCurve, RollCurveUpdate);

	FVector RollDirection = GetActorForwardVector().RotateAngleAxis(UpdateRollCurve(RollTimeline.GetPlaybackPosition()), FVector{ 0.0f, 0.0f, 1.0f });
	
	GetCharacterMovement()->Velocity = RollDirection;

	RollTimeline.PlayFromStart();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlayerableCharacter::EnableInputAfterRoll, RollTimeline.GetTimelineLength(), false);
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