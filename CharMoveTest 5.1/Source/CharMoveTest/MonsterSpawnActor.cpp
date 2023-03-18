// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawnActor.h"

// Sets default values
AMonsterSpawnActor::AMonsterSpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMonsterSpawnActor::MonsterSpawn()
{
	const FVector Location = GetActorLocation();
	const FRotator Rotation = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(ActorToSpawn, Location, Rotation);
}

// Called when the game starts or when spawned
void AMonsterSpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}


