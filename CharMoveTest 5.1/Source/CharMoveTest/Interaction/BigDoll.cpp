// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Interaction/BigDoll.h"

// Sets default values
ABigDoll::ABigDoll()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABigDoll::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABigDoll::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

