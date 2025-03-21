// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boss_Struct.generated.h"


USTRUCT(BlueprintType)
struct FBossInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "BossInfo")
	float BossHP;
	UPROPERTY(EditAnywhere, Category = "BossInfo")
	float MaxBossHP;
};

USTRUCT(BlueprintType)
struct FBearDollInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll")
	float Control_DetectRadius = 500.f; //범위 반지름
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

USTRUCT(BlueprintType)
struct FBearDollFallObjInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_Speed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_Acceleration = 1.4f; //가속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_time = 1.0f; //충돌 오브젝트 공격 범위가 생성되는 주기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_Delay = 1.5f; //충돌 오브젝트가 생성되기까지 딜레이
};

USTRUCT(BlueprintType)
struct FPlasticDollInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlasticDoll")
	float PD_Hit_Delay; //플레이어 추격 Obj가 가다가 멈출때까지의 딜레이 
};

UCLASS()
class CHARMOVETEST_API ABoss_Struct : public AActor
{
	GENERATED_BODY()

public:	
	ABoss_Struct();

private:
	UPROPERTY()
	FBearDollInfo BearDollInfo;
	UPROPERTY()
	FBearDollFallObjInfo BearDollFallObjInfo;
	UPROPERTY()
	FPlasticDollInfo PlasticDollInfo;

public:
	UFUNCTION()
	float GetDetectRadius();
	UFUNCTION(BlueprintCallable)
	FBearDollInfo GetBearDollInfo() const;
	UFUNCTION(BlueprintCallable)
	FBearDollFallObjInfo GetBearDollFallObjInfo() const;
	UFUNCTION(BlueprintCallable)
	FPlasticDollInfo GetPlasticDollInfo() const;
};
