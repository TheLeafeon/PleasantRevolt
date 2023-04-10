// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMonsterArea.h"
#include "TestMonster.h"
#include "TestCharacter.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Engine.h"

// Sets default values
ATestMonsterArea::ATestMonsterArea()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	firstIn = false;

	bSpawn = false;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnPointCom"));
	CollisionSphere->InitSphereRadius(800.0f);
	RootComponent = CollisionSphere;

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATestMonsterArea::OnOverlapBegin);

	Wave2Start = false;
	numberOfMonstersDefeafed = 0;
	thisAreaWaveNumber = 1;
}

// Called when the game starts or when spawned
void ATestMonsterArea::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATestMonsterArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (thisAreaWaveNumber >= 2)
	{
		if (numberOfMonstersDefeafed != 0 && numberOfMonstersDefeafed == AreaSpawnMonsterArray.Num())
		{
			Wave2Spawn();
		}
	}


}

void ATestMonsterArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	if (!firstIn)
	{
		firstIn = true;

		if (InLinkDoor != nullptr)
		{
			InLinkDoor->CloseDoor();
		}

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

void ATestMonsterArea::Wave2Spawn()
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



