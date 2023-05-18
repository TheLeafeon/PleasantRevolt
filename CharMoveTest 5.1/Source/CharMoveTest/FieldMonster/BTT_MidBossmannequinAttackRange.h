// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MidBossmannequinAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBTT_MidBossmannequinAttackRange : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_MidBossmannequinAttackRange();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY()
		float AttackRangeRadiusSize; //공격 인식 범위

	
};
