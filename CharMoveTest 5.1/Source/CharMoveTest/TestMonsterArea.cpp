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

	

}

// Called when the game starts or when spawned
void ATestMonsterArea::BeginPlay()
{
	Super::BeginPlay();
	
	//DrawDebugSphere(GetWorld(), GetActorLocation(), 800.0f, 50, FColor::Green, true, -1, 0, 2);

}

// Called every frame
void ATestMonsterArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ATestMonsterArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	

	if (!firstIn)
	{
		firstIn = true;

		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Overlap"));

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



