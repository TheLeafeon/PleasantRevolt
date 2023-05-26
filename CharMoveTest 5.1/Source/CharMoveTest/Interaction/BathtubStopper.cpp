// Fill out your copyright notice in the Description page of Project Settings.

#include "BathtubStopper.h"

// Sets default values
ABathtubStopper::ABathtubStopper()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	RootComponent = _RootComponent;

	BathtubStopperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BathtubStopperMesh"));
	BathtubStopperMesh->SetupAttachment(RootComponent);
	BathtubStopperMesh->SetSimulatePhysics(true);

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget"));
	InteractionWidget->SetupAttachment(RootComponent);

	Target = nullptr;
	isLaunch = false;
	LaunchForce = 1000.0f;
}

void ABathtubStopper::BeginPlay()
{
	Super::BeginPlay();

	InteractionWidget->SetVisibility(false);
}

void ABathtubStopper::InteractWithMe()
{
	LaunchActor();
	DeleteTarget();
}

void ABathtubStopper::ShowInteractionWidget()
{
	if (isLaunch)
		return;
	InteractionWidget->SetVisibility(true);
}

void ABathtubStopper::HideInteractionWidget()
{
	InteractionWidget->SetVisibility(false);
}

void ABathtubStopper::LaunchActor()
{
	if (isLaunch)
		return;

	FVector LaunchDirection = FVector::UpVector;
	LaunchDirection.Normalize();

	FVector LaunchVelocity = LaunchDirection * LaunchForce;
	BathtubStopperMesh->AddImpulse(LaunchVelocity, NAME_None, true);

	isLaunch = true;
	HideInteractionWidget();
}

void ABathtubStopper::DeleteTarget()
{
	if (Target == nullptr)
		return;

	Target->Destroy();
}