// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Interaction/MovingBasket.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"

// Sets default values
AMovingBasket::AMovingBasket()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InterpSpeed = 5.0f;

	BasketComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Basket"));
	BasketComp->SetupAttachment(RootComponent);

	firstIn = false;
	ropeBreak = false;
	firstSectionArrive = false;
	arrive = false;
}

// Called when the game starts or when spawned
void AMovingBasket::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();

	CutropeTargetLocation = CutropeTargetActor->GetActorLocation();
	TargetLocation = TargetActor->GetActorLocation();
	
	SecondTargetLocation= SecondTargetActor->GetActorLocation();
}

// Called every frame
void AMovingBasket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (firstIn)
	{
		//로프 끊어지는 부분까지 이동
		if (!ropeBreak)
		{
			FVector CurrentLocation = GetActorLocation();

			FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, CutropeTargetLocation, DeltaTime, InterpSpeed);
			SetActorLocation(NewLocation);

			if (CurrentLocation.Equals(CutropeTargetLocation, 10.0f))
			{
				ropeBreak = true;
				ShakeBasket();
			}
		}

		if (ropeBreak)
		{
			if (!firstSectionArrive)
			{
				FVector CurrentLocation = GetActorLocation();

				FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, InterpSpeed);
				SetActorLocation(NewLocation);

				if (CurrentLocation.Equals(TargetLocation, 10.0f))
				{
					firstSectionArrive = true;
				}
			}
		}

		if (firstSectionArrive == !arrive)
		{
			FVector CurrentLocation = GetActorLocation();

			FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, SecondTargetLocation, DeltaTime, InterpSpeed);
			SetActorLocation(NewLocation);

			if (CurrentLocation.Equals(SecondTargetLocation, 10.0f))
			{
				arrive = true;
				BasketComp->SetSimulatePhysics(true);

				FTimerHandle NextLevelHandle;

				FTimerDelegate NextLevelDelegate = FTimerDelegate::CreateUObject(this, &AMovingBasket::GoToStudioLevel);
				GetWorldTimerManager().SetTimer(NextLevelHandle, NextLevelDelegate, 2.0f, false);
			}
		}

	}
}

void AMovingBasket::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}





