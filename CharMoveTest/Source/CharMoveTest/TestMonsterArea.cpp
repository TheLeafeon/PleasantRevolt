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


	/*if (bSpawn)
	{
		currentTime = currentTime + 1 * DeltaTime;

		if (currentTime > 2.0f)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = GetInstigator();

			UWorld* WRLD = GetWorld();

			FVector location = GetActorLocation();
			FRotator rotation = GetActorRotation();

			ATestMonster* myNewBot = WRLD->SpawnActor<ATestMonster>(myBot[0], location, rotation);

			currentTime = 0.0f;
		}

	}*/

}

void ATestMonsterArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Overlap"));

	//LinkDoor->CloseDoor();

	if (!firstIn)
	{
		LinkDoor->CloseDoor();
		firstIn = true;
	}

	/*if (OtherActor->IsA(ATestCharacter::StaticClass()))
	{
		if (!bSpawn)
		{
			bSpawn = true;
		}
	}*/
}



