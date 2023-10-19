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
	//BearDoll
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll")
	float Control_DetectRadius; //���� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll")
	float BearDoll_RushSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll")
	float RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll")
	float Rush_Delay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll")
	float Rotation_Delay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll")
	float Follow_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll")
	float Follow_Time;

	//BearDoll FallObj
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_Acceleration; //���ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_time; //�浹 ������Ʈ ���� ������ �����Ǵ� �ֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_Delay; //�浹 ������Ʈ�� �����Ǳ���� ������

	//PlasticDoll
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlasticDoll")
	float PD_Hit_Delay; //�÷��̾� �߰� Obj�� ���ٰ� ���⶧������ ������ 
};
