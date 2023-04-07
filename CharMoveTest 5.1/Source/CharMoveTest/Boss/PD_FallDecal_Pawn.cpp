// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PD_FallDecal_Pawn.h"

// Sets default values
APD_FallDecal_Pawn::APD_FallDecal_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APD_FallDecal_Pawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APD_FallDecal_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APD_FallDecal_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector APD_FallDecal_Pawn::GetFallDecalPos()
{
	return GetActorLocation();
}
