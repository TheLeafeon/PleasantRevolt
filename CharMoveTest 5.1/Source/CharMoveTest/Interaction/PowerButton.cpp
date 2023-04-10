// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Interaction/PowerButton.h"
#include "PowerButton.h"

// Sets default values
APowerButton::APowerButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	RootComponent = _RootComponent;

	InteractionSampleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SampleMesh"));
	InteractionSampleMesh->SetupAttachment(RootComponent);

	PowerOn = false;
}

void APowerButton::InteractWithMe()
{
	if (!PowerOn)
	{
		PowerOn = true;
		PowerButtonInteraction();
	}
}

void APowerButton::ShowInteractionWidget()
{
}

// Called when the game starts or when spawned
void APowerButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

