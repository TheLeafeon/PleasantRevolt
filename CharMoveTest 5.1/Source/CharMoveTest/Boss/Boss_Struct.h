// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Boss_Struct.generated.h"

class CHARMOVETEST_API Boss_Struct
{
public:	
	Boss_Struct();
	~Boss_Struct();
};

USTRUCT(Atomic, BlueprintType)
struct FBossInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "BossInfo")
	float BossHP;
	UPROPERTY(EditAnywhere, Category = "BossInfo")
	float MaxBossHP;
};

USTRUCT(Atomic, BlueprintType)
struct FBearDollInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll")
	float Control_DetectRadius = 500.f; //���� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll")
	float BearDoll_RushSpeed = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll")
	float RotationSpeed = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll")
	float Rush_Delay = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll")
	float Rotation_Delay = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll")
	float Follow_Speed = 350.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll")
	float Follow_Time = 3.f;
};

USTRUCT(Atomic, BlueprintType)
struct FBearDollFallObjInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_Speed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_Acceleration = 1.4f; //���ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_time = 1.0f; //�浹 ������Ʈ ���� ������ �����Ǵ� �ֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_Delay = 1.5f; //�浹 ������Ʈ�� �����Ǳ���� ������
};

USTRUCT(Atomic, BlueprintType)
struct FPlasticDollInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlasticDoll")
	float PD_Hit_Delay; //�÷��̾� �߰� Obj�� ���ٰ� ���⶧������ ������ 
};