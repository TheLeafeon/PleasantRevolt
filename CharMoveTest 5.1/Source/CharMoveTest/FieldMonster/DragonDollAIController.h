// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DragonDollAIController.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API ADragonDollAIController : public AAIController
{
	GENERATED_BODY()
	

public:
	ADragonDollAIController();

	virtual void OnPossess(APawn* InPawn) override;

	static const FName HomePosKey;
	static const FName TargetKey;

private:
	UPROPERTY()
		class UBehaviorTree* BTDragonDoll;
	UPROPERTY()
		class UBlackboardData* BBDragonDoll;
};
