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
	//BearDoll AI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detect_BTService")
	float Control_DetectRadius; //범위 반지름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BearDoll_RushSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Rush_Delay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Rotation_Delay;

	//BearDoll FallObj
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Fall_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Fall_Acceleration; //가속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Fall_time; //충돌 오브젝트 공격 범위가 생성되는 주기
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Fall_Delay; //충돌 오브젝트가 생성되기까지 딜레이
};
