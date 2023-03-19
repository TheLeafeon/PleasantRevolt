// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "BTTask_GirlDollFindPatrolPos.generated.h"

/**
 *
 */
UCLASS()
class CHARMOVETEST_API UBTTask_GirlDollFindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_GirlDollFindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};