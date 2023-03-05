// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMonsterSpawner::MonsterSpawn()
{
	const FVector Location = GetActorLocation();
	const FRotator Rotation = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(ActorToSpawn, Location, Rotation);
}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();

	
	
}

//// Called every frame
//void AMonsterSpawner::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

