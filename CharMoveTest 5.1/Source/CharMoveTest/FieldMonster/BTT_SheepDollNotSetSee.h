// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_SheepDollNotSetSee.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBTT_SheepDollNotSetSee : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_SheepDollNotSetSee();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
