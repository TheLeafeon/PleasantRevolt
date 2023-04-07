// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PlasticDoll_Arm.h"

UPlasticDoll_Arm::UPlasticDoll_Arm() : SavePos(0)
{

}

void UPlasticDoll_Arm::Smash(const AActor*& SmashArm)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Smash"));
}

void UPlasticDoll_Arm::SetFallDecalPos(const FVector& FallDecalPos)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Save"));
	SavePos = FallDecalPos;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (*SavePos.ToString()));
}

FVector UPlasticDoll_Arm::GetFallDecalPos()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, (*SavePos.ToString()));
	return SavePos;
}