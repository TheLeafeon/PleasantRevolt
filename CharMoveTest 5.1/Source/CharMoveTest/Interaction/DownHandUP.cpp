// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Interaction/DownHandUP.h"

// Sets default values(
ADownHandUP::ADownHandUP() : IsHandUp(false), IsMirror(false), IsDown(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADownHandUP::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCharacter = Cast<APlayerableCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter != nullptr)
	{
		AnimInstance = Cast<UPlayerAnimInstnce>(PlayerCharacter->GetMesh()->GetAnimInstance());
	}

	SaveZ = GetActorLocation().Z;
}

// Called every frame
void ADownHandUP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDown)
	{
		FVector NewLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 2.0f);
		SetActorLocation(NewLocation);

		if (FMath::IsNearlyEqual(GetActorLocation().Z, SaveZ, 1.0f))
		{
			IsDown = false;
			SetMirrorHandUp();
		}
	}
}

void ADownHandUP::InteractWithMe()
{
	if (PlayerCharacter->IsHandUp && IsHandUp)
	{
		DestroyMirrorHandUp();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("down"));
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADownHandUP::Down, 0.65f, false);

		HandUpAni(false);

		PlayerCharacter->SetInterface();
	}
	else if (PlayerCharacter->IsHandUp == false && !IsHandUp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("up"));
		//CollisionComponent->SetCollisionProfileName(TEXT("InteractionObj_O"));
		BlockCollisionComponent->SetCollisionProfileName(TEXT("OverlapAll"));
		CollisionComponent->SetSimulatePhysics(false);
		PlayerCharacter->PlayerHandUp(this);
		HideInteractionWidget();

		HandUpAni(true);

		IsHandUp = true;
	}

}

void ADownHandUP::ShowInteractionWidget()
{
	if (!IsHandUp && PlayerCharacter->IsHandUp == false)
	{
		InteractionWidget->SetVisibility(true);
	}
}

void ADownHandUP::HideInteractionWidget()
{
	InteractionWidget->SetVisibility(false);
}

void ADownHandUP::SetFalsePhysics()
{
	CollisionComponent->SetSimulatePhysics(false);
}

void ADownHandUP::Drop()
{
	if (IsHandUp)
	{
		DestroyMirrorHandUp();
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADownHandUP::Down, 0.1f, false);

		HandUpAni(false);
	}
}

void ADownHandUP::BackDrop()
{
	if (IsHandUp)
	{
		DestroyMirrorHandUp();
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ADownHandUP::BackDown, 0.1f, false);

		HandUpAni(false);
	}
}

void ADownHandUP::Down()
{
	BlockCollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));

	const FRotator Rotation = PlayerCharacter->GetActorRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * 250;

	SetActorLocation(PlayerCharacter->GetActorLocation() + Direction);
	SetActorRotation(PlayerCharacter->GetActorRotation());

	IsDown = true;
	PlayerCharacter->IsHandUp = false;
	IsHandUp = false;
}

void ADownHandUP::BackDown()
{
	BlockCollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));

	const FRotator Rotation = PlayerCharacter->GetActorRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * -250;

	SetActorLocation(PlayerCharacter->GetActorLocation() + Direction);
	SetActorRotation(FRotator(0, 0, GetActorRotation().Yaw));

	IsDown = true;
	PlayerCharacter->IsHandUp = false;
	IsHandUp = false;
}