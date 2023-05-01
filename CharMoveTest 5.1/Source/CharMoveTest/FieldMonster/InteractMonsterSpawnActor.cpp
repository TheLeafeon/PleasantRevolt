// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/InteractMonsterSpawnActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractMonsterSpawnActor::AInteractMonsterSpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	RootComponent = _RootComponent;

	InteractionSampleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SampleMesh"));
	InteractionSampleMesh->SetupAttachment(RootComponent);

	
	bIsMonsterSpawned = false;

	numberOfMonstersDefeafed = 0;

}

// Called when the game starts or when spawned
void AInteractMonsterSpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractMonsterSpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	numberOfMonstersDefeafed = MyArea->numberOfMonstersDefeafed;
	if (numberOfMonstersDefeafed != 0 && numberOfMonstersDefeafed == SpawnMonsterArray.Num())
	{
		AreaClear = true;
	}

}

void AInteractMonsterSpawnActor::InteractWithMe()
{
	
	if (!bIsMonsterSpawned)
	{
		bIsMonsterSpawned = true;

		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("MonsterSpawn"));

		if (SpawnMonsterArray.Num() == 0)
		{
			return;
		}
		for (int ArrayCount = 0; ArrayCount < SpawnMonsterArray.Num(); ArrayCount++)
		{
			SpawnMonsterArray[ArrayCount]->MonsterSpawn();
		}


	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("AlreadyMonsterSpawn"));
	}
	
	

}

void AInteractMonsterSpawnActor::ShowInteractionWidget()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("You press E"));
}

