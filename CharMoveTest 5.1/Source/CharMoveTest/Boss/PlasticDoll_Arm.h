// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlasticDoll_Arm.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UPlasticDoll_Arm : public UObject
{
	GENERATED_BODY()
	
public:
	UPlasticDoll_Arm();

	//팔에서 공통적으로 쓸 함수 및 변수
	void Smash(const AActor*& SmashArm);
	void SetFallDecalPos(const FVector& FallDecalPos);
	FVector GetFallDecalPos();

private:
	FVector SavePos;
};
