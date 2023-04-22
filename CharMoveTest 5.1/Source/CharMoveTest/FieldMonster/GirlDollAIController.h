// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/GirlDoll.h"
#include "AIController.h"
#include "GirlDollAIController.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API AGirlDollAIController : public AAIController
{
	GENERATED_BODY()
public:
	AGirlDollAIController();

	virtual void OnPossess(APawn* InPawn)override;

	void OnPossessDelayed(APawn* InPawn);

	static const FName HomePosKey;
	static const FName TargetKey;
	static const FName AreaPosKey;
	static const FName AreaSizeKey;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
		AGirlDoll* MyGirlDoll;
private:
	UPROPERTY()
		class UBehaviorTree* BTGirlDoll;
	UPROPERTY()
		class UBlackboardData* BBGirlDoll;

	
};
