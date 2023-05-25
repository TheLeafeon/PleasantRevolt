// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Interaction/IKey.h"

// Sets default values
AIKey::AIKey() : IsGet(false), IsMidKey(false), MidKeyPos(0.0f), TotalTime(2.5f), CurrentTime(0.0f), StartTime(0.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AIKey::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AIKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsMidKey)
	{
		// 현재 시간을 계산합니다.
		CurrentTime = GetWorld()->GetTimeSeconds() - StartTime;

		// 보간 계산을 위한 알파 값을 계산합니다.
		Alpha = FMath::Clamp(CurrentTime / TotalTime, 0.0f, 1.0f);

		// 보간된 위치를 계산합니다.
		NewLocation = FMath::Lerp(StartLocation, TargetLocation, Alpha);

		// 액터의 위치를 업데이트합니다.
		SetActorLocation(NewLocation);

		if (GetActorLocation().Equals(TargetLocation, 0.1))
		{
			IsMidKey = false;
		}
	}
}

void AIKey::InteractWithMe()
{
	if (!IsGet)
	{
		IsGet = true;
		CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

		HideInteractionWidget();
	}
}

void AIKey::ShowInteractionWidget()
{
	if (!IsGet)
	{
		InteractionWidget->SetVisibility(true);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("You press E"));
}

void AIKey::HideInteractionWidget()
{
	InteractionWidget->SetVisibility(false);
}

void AIKey::MidKey()
{
	if (MidKeyActor)
	{
		IsMidKey = true;
		MidKeyPos = MidKeyActor->GetActorLocation().Z;
		StartTime = GetWorld()->GetTimeSeconds();
		StartLocation = GetActorLocation();
		TargetLocation = FVector(GetActorLocation().X, GetActorLocation().Y, MidKeyPos);
	}
}