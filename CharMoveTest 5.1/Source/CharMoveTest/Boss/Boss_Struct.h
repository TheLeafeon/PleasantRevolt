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
	float Control_DetectRadius; //범위 반지름
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
};

USTRUCT(Atomic, BlueprintType)
struct FBearDollFallObjInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_Speed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_Acceleration = 1.4f; //가속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_time = 1.0f; //충돌 오브젝트 공격 범위가 생성되는 주기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_Delay = 1.5f; //충돌 오브젝트가 생성되기까지 딜레이
};

USTRUCT(Atomic, BlueprintType)
struct FPlasticDollInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlasticDoll")
	float PD_Hit_Delay; //플레이어 추격 Obj가 가다가 멈출때까지의 딜레이 
};