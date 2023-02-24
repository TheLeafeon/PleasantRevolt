// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "TestDoorOpenBox.h"

#include "Camera/CameraComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATestCharacter::ATestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1000.0f;
	CameraBoom->TargetOffset=FVector(.0f,600.f,600.f);
	
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));

	
	
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	

	
	
	FollowCamera->bUsePawnControlRotation = false;


}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ATestCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATestCharacter::MoveRight);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &ATestCharacter::TryInteraction);

}

void ATestCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f) && (CharMoveAllow == true))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}
void ATestCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f) && (CharMoveAllow == true))
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

void ATestCharacter::TryInteraction()
{
	FHitResult HitResult;
	const TArray<AActor*> IgnoreActors = { this };
	const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { UEngineTypes::ConvertToObjectType(ECC_WorldStatic),
		UEngineTypes::ConvertToObjectType(ECC_WorldDynamic) };

	const FVector StartLocation = GetActorLocation();
	const FVector EndLocation = StartLocation + GetActorForwardVector() * 150.0f;

	bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), StartLocation, EndLocation,
		30.0f, ObjectTypes, false, IgnoreActors, EDrawDebugTrace::ForDuration, HitResult, true);

	if (bHit && HitResult.bBlockingHit)
	{
		if (HitResult.GetActor() != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Interaction"));

			if (HitResult.GetActor()->IsA(ATestDoorOpenBox::StaticClass()))
			{
				ATestDoorOpenBox* HitBox = Cast<ATestDoorOpenBox>(HitResult.GetActor());

				if (HitBox == nullptr) return;

				MoveCamera(HitBox->LinkDoorCameraLocation);

				
				//HitBox->ShowOpenDoor(FollowCamera);
				HitBox->TryOpenDoor();
				

				//CharMoveAllow = false;
			}

		}
	}

}



