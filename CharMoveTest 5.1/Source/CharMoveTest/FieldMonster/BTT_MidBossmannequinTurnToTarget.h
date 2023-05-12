// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MidBossmannequinTurnToTarget.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBTT_MidBossmannequinTurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_MidBossmannequinTurnToTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	

private:
	bool TurnEnd;

	float TurnTime;


};
