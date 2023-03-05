// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerableCharacter.h"
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

	// Player Status
	Player_HP = 4.0f;
	Player_Speed = 0.0f;
	Player_Roll_Test = 600.0f;
	Player_Attack_Power = 0.0f;
	Player_Attack_Near_Distance = 0.0f;
	Player_Attack_Far_Distance = 0.0f;

	// Player Melee
	isAttack = false;
}

// Called to bind functionality to input
void APlayerableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Rolling", IE_Released, this, &APlayerableCharacter::Rolling);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerableCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerableCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerableCharacter::TurnAtRate);
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

}

void APlayerableCharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Cast<UPlayerAnimInstnce>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance)
		return;
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

void APlayerableCharacter::Decrease_Player_HP(float val)
{
	Player_HP -= val;
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

	FTimerHandle TimerHandle;
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

//=============== Player Roll =============== //

void APlayerableCharacter::Rolling()
{
	AnimInstance->PlaySampleMontage();

	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		CurveTimeline.SetLooping(false);

		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT(" Screen"));
	}

	CurveTimeline.PlayFromStart();


	//FVector sample = GetActorForwardVector() * CurveTimeline.GetTimelineLength() * GetCharacterMovement()->GetMaxSpeed() * 2.0f;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Debug %f"), CurveTimeline.GetTimelineLength()));
	FVector sample = GetActorForwardVector() * (CurveTimeline.GetTimelineLength() * Player_Roll_Test);
	
	GetCharacterMovement()->Velocity = sample;
}