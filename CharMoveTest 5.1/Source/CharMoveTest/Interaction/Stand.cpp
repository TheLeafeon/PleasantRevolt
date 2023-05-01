// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Interaction/Stand.h"

// Sets default values
AStand::AStand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	RootComponent = _RootComponent;

	InteractionSampleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SampleMesh"));
	InteractionSampleMesh->SetupAttachment(RootComponent);

	StandMove = false;
}

void AStand::InteractWithMe()
{
	if (!StandMove)
	{
		StandMove = true;
		StandRotation();
		DuckDoll->FallDoll();
	}
}

void AStand::ShowInteractionWidget()
{
}

// Called when the game starts or when spawned
void AStand::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

