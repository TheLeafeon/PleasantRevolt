// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITMonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API AAITMonsterAIController : public AAIController
{
	GENERATED_BODY()
public:
	AAITMonsterAIController();

	virtual void OnPossess(APawn* InPawn)override;

	static const FName HomePosKey;
	static const FName TargetKey;
private:
	UPROPERTY()
		class UBehaviorTree* BTAITMonster;
	UPROPERTY()
		class UBlackboardData* BBAITMonster;

	
};
