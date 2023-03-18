// Fill out your copyright notice in the Description page of Project Settings.


#include "TestDoorOpenBox.h"

// Sets default values
ATestDoorOpenBox::ATestDoorOpenBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestDoorOpenBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestDoorOpenBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATestDoorOpenBox::TryOpenDoor()
{
	if (OpenableDoor == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Open"));
		OpenableDoor = false;

		LinkDoor->OpenDoor();

		//OpenDoorAction();
	}
}
