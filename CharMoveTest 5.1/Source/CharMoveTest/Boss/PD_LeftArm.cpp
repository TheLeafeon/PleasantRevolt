// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PD_LeftArm.h"

// Sets default values
APD_LeftArm::APD_LeftArm()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APD_LeftArm::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APD_LeftArm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APD_LeftArm::Smash()
{
	UPlasticDoll_Arm::Smash();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Left"));
}

void APD_LeftArm::SmashWait()
{
	//들어올리는 애니메이션
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Left SmashWait"));
}

void APD_LeftArm::BackSmash()
{
	//다시 원상태로 돌리는 애니메이션
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Left BackSmash"));
}