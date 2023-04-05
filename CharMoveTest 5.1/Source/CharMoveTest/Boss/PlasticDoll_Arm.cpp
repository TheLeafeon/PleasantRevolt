// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PlasticDoll_Arm.h"

UPlasticDoll_Arm::UPlasticDoll_Arm()
{

}

void UPlasticDoll_Arm::Smash()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Smash"));
}