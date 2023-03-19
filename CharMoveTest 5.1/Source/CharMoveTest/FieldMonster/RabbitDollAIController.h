// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RabbitDollAIController.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API ARabbitDollAIController : public AAIController
{
	GENERATED_BODY()


public:

	ARabbitDollAIController();

	virtual void OnPossess(APawn* InPawn) override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;

private:
	UPROPERTY()
		class UBehaviorTree* BTRabbitDoll;
	UPROPERTY()
		class UBlackboardData* BBRabbitDoll;
	
};
