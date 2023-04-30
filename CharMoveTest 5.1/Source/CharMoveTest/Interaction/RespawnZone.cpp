// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Interaction/RespawnZone.h"

// Sets default values
ARespawnZone::ARespawnZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RespawnZone"));
	CollisionBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	RootComponent = CollisionBox;
}

// Called when the game starts or when spawned
void ARespawnZone::BeginPlay()
{
	Super::BeginPlay();
	
	if (SpawnPoint == nullptr)
	{
		return;
	}


}

// Called every frame
void ARespawnZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



