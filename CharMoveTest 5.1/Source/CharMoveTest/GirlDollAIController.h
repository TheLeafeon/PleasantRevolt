// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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


	virtual void OnPossess(APawn* InPawn) override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;


private:
	UPROPERTY()
		class UBehaviorTree* BTGirlDoll;

	UPROPERTY()
		class UBlackboardData* BBGirlDoll;

};
