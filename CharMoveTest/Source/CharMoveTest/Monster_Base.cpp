// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Base.h"
#include "Components/SphereComponent.h"

// Sets default values
AMonster_Base::AMonster_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Monster_Attack_Distance = CreateDefaultSubobject<USphereComponent>(TEXT("Monster_Attack_Distance"));
	Monster_Attack_Distance->InitSphereRadius(100.0f);
}

// Called when the game starts or when spawned
void AMonster_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonster_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

