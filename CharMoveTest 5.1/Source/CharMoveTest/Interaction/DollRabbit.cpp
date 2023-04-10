// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Interaction/DollRabbit.h"

// Sets default values
ADollRabbit::ADollRabbit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADollRabbit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADollRabbit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADollRabbit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

