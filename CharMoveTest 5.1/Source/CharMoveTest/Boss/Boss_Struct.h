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

USTRUCT(BlueprintType)
struct FBearDollFallObjInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_Speed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_Acceleration = 1.4f; //���ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_time = 1.0f; //�浹 ������Ʈ ���� ������ �����Ǵ� �ֱ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BearDoll FallObj")
	float Fall_Delay = 1.5f; //�浹 ������Ʈ�� �����Ǳ���� ������
};

USTRUCT(BlueprintType)
struct FPlasticDollInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlasticDoll")
	float PD_Hit_Delay; //�÷��̾� �߰� Obj�� ���ٰ� ���⶧������ ������ 
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
