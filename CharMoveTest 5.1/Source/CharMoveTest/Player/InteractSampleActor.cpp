// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractSampleActor.h"

// Sets default values
AInteractSampleActor::AInteractSampleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsOn = false;

	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	RootComponent = _RootComponent;

	InteractionSampleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SampleMesh"));
	InteractionSampleMesh->SetupAttachment(RootComponent);

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget"));
	InteractionWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractSampleActor::BeginPlay()
{
	Super::BeginPlay();

	InteractionWidget->SetVisibility(false);
}

// Called every frame
void AInteractSampleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractSampleActor::InteractWithMe()
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

void AInteractSampleActor::ShowInteractionWidget()
{
	InteractionWidget->SetVisibility(true);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("You press E"));

}

void AInteractSampleActor::HideInteractionWidget()
{
	InteractionWidget->SetVisibility(false);
}