// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BossAI_GameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBossAI_GameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	UBossAI_GameInstanceSubsystem();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detect_BTService")
	float Control_DetectRadius; //범위 반지름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BearDoll_RushSpeed;
};
