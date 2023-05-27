// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MouseDollTurnToTarget.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBTT_MouseDollTurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:

		UBTT_MouseDollTurnToTarget();

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	float StartTime;
	
};
