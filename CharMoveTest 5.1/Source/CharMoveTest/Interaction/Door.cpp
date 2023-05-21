// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Interaction/Door.h"

// Sets default values
ADoor::ADoor() : IsDoorActive(false), Complete(false), IsKeyDoor(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::InteractWithMe()
{
	if (IsDoorActive && !Complete && IsKeyDoor)
	{
		Down();
		HideInteractionWidget();

		Complete = true;
	}
}

void ADoor::ShowInteractionWidget()
{
	if (IsKeyDoor)
	{
		if (!IsDoorActive)
		{
			KeyCheck();
		}
		if (IsDoorActive && !Complete)
		{
			InteractionWidget->SetVisibility(true);
		}
	}
}

void ADoor::HideInteractionWidget()
{
	if (IsKeyDoor)
	{
		InteractionWidget->SetVisibility(false);
	}
}