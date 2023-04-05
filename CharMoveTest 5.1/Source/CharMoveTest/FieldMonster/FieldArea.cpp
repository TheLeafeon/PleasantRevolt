// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/FieldArea.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Engine.h"

// Sets default values
AFieldArea::AFieldArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	firstIn = false;

	bSpawn = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnPointCom"));
	CollisionBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFieldArea::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AFieldArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFieldArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFieldArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!firstIn)
	{
		firstIn = true;

		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Overlap"));


		if (AreaSpawnMonsterArray.Num() == 0)
		{
			return;
		}
		for (int ArrayCount = 0; ArrayCount < AreaSpawnMonsterArray.Num(); ArrayCount++)
		{
			AreaSpawnMonsterArray[ArrayCount]->MonsterSpawn();
		}
	}
}

void AFieldArea::Wave2Spawn()
{
	if (!Wave2Start)
	{
		if (AreaSpawnMonsterArrayWave2.Num() == 0)
		{
			return;
		}
		for (int ArrayCount = 0; ArrayCount < AreaSpawnMonsterArrayWave2.Num(); ArrayCount++)
		{
			AreaSpawnMonsterArrayWave2[ArrayCount]->MonsterSpawn();

		}
		Wave2Start = true;
	}
}

