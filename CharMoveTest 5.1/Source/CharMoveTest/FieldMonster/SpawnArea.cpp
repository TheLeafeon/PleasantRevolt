// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/SpawnArea.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"

// Sets default values
ASpawnArea::ASpawnArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	firstIn = false;
	myAreaClear = false;
	bSpawn = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnPointCom"));
	CollisionBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASpawnArea::OnOverlapBegin);
}

void ASpawnArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ASpawnArea::MonsterSpawn()
{
	if (AreaSpawnMonsterArray.Num() == 0)
	{
		return;
	}
	for (int ArrayCount = 0; ArrayCount < AreaSpawnMonsterArray.Num(); ArrayCount++)
	{
		AreaSpawnMonsterArray[ArrayCount]->MonsterSpawn();
	}
}

// Called when the game starts or when spawned
void ASpawnArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

