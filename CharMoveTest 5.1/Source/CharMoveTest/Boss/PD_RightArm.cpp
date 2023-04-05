// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PD_RightArm.h"

// Sets default values
APD_RightArm::APD_RightArm()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APD_RightArm::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APD_RightArm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APD_RightArm::Smash()
{
	UPlasticDoll_Arm::Smash();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Right"));
}

void APD_RightArm::SmashWait()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Right SmashWait"));
}

void APD_RightArm::BackSmash()
{
	//다시 원상태로 돌리는 애니메이션
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Right BackSmash"));
}