// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Interaction/lever_A.h"

// Sets default values
Alever_A::Alever_A()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Alever_A::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Alever_A::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Alever_A::InteractWithMe()
{
	// On/Off 상호작용
	if (bIsOn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Interact"));
		bIsOn = false;
	}
	else
	{
		bIsOn = true;
	}
}

void Alever_A::ShowInteractionWidget()
{
	InteractionWidget->SetVisibility(true);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("You press E"));

}

void Alever_A::HideInteractionWidget()
{
	InteractionWidget->SetVisibility(false);
}