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
	float Control_DetectRadius; //���� ������
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
	float Fall_Acceleration; //���ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Fall_time; //�浹 ������Ʈ ���� ������ �����Ǵ� �ֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Fall_Delay; //�浹 ������Ʈ�� �����Ǳ���� ������
};
