// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/RabbitDoll.h"
#include "CharMoveTest/TestCharacter.h"
#include "CharMoveTest/FieldMonster/RabbitDollAIController.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Engine.h"


ARabbitDoll::ARabbitDoll()
{
	AIControllerClass = ARabbitDollAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Monster_HP = 2.0f;
	Monster_Power = 1.0f;
	Monster_Speed = 1.0f;
	Monster_Attack_Time = 1.0f;
	Monster_Attack_Delay = 0.5f;
	Monster_Knockback_Time = 0.5;
}

void ARabbitDoll::BeginPlay()
{
	Super::BeginPlay();

	MyArea = FindClosestMonsterArea();
	MyAreaSize = MyArea->CollisionSphere->GetScaledSphereRadius();
	MyAreaLocation = MyArea->GetActorLocation();

}



ATestMonsterArea* ARabbitDoll::FindClosestMonsterArea()
{
	TArray<AActor*> OverlappingActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATestMonsterArea::StaticClass(), OverlappingActors);

	ATestMonsterArea* ClosestArea = nullptr;
	FVector RabbitDollLocation = GetActorLocation();
	float MinDistance = TNumericLimits<float>::Max();

	for (AActor* Actor : OverlappingActors)
	{
		ATestMonsterArea* Area = Cast<ATestMonsterArea>(Actor);
		if (Area != nullptr)
		{
			float Distance = FVector::Distance(RabbitDollLocation, Area->GetActorLocation());
			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				ClosestArea = Area;
			}
		}
	}



	return ClosestArea;
}
