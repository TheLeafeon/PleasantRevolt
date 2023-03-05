// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMonster.h"

// Sets default values
ATestMonster::ATestMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void ATestMonster::BeginPlay()
{
	Super::BeginPlay();

	const FVector Location = GetActorLocation();
	const FRotator Rotation = GetActorRotation();
	GetWorld()->SpawnActor<AActor>(ActorToSpawn, Location, Rotation);

	
}

//// Called every frame
//void ATestMonster::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

// Called to bind functionality to input
void ATestMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

