// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Interaction/Basket.h"
#include "Engine/EngineTypes.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "TimerManager.h"
#include "Misc/App.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "Basket.h"

// Sets default values
ABasket::ABasket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerSit = CreateDefaultSubobject<UBoxComponent>(TEXT("BasketOverlapBox"));
	BasketOverlapBoxSize = FVector(100.0f, 100.0f, 20.0f);

	PlayerSit->SetBoxExtent(BasketOverlapBoxSize);
	//PlayerSit->SetupAttachment(GetMesh());

	PlayerSit->OnComponentBeginOverlap.AddDynamic(this, &ABasket::OnOverlapBegin);

	firstIn = false;

}

// Called when the game starts or when spawned
void ABasket::BeginPlay()
{
	Super::BeginPlay();
	
	TargetActorLocation = TargetActor->GetActorLocation();
	StudioTargetActorLocation = StudioTargetActor->GetActorLocation();
}

// Called every frame
void ABasket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasket::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (!firstIn)
	{
		firstIn = true;
		FTimerHandle BasketRotationHandle;


		//MoveBasket();
		FTimerDelegate BasketMoveDelegate = FTimerDelegate::CreateUObject(this, &ABasket::MoveBasket);
		GetWorldTimerManager().SetTimer(BasketMoveHandle, BasketMoveDelegate, 0.01f, true);

		FTimerDelegate BasketRotationDelegate = FTimerDelegate::CreateUObject(this, &ABasket::BasketRotationChange);
		GetWorldTimerManager().SetTimer(BasketRotationHandle, BasketRotationDelegate, 3.0f, false);


	}

}

void ABasket::MoveBasket()
{


	FVector BasketLocation = GetActorLocation();
	FVector TargetLocation = TargetActor->GetActorLocation();

	FVector MoveDirection = (TargetLocation - BasketLocation).GetSafeNormal();

	MoveDirection.Normalize();
	FVector NewLocation = GetActorLocation() + MoveDirection * 500.0f * GetWorld()->DeltaTimeSeconds;
	SetActorLocation(NewLocation);

	if (FMath::IsNearlyEqual(NewLocation.X, TargetLocation.X,500) && FMath::IsNearlyEqual(NewLocation.Y, TargetLocation.Y,500) && FMath::IsNearlyEqual(NewLocation.Z, TargetLocation.Z,500)) // 목표 위치에 도달했을 때 타이머 종료
	{
		StudioTeleport();
		GetWorld()->GetTimerManager().ClearTimer(BasketMoveHandle);
	}


	
}

