// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MidBossmannequinSetSee.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBTT_MidBossmannequinSetSee : public UBTTaskNode
{
	GENERATED_BODY()
public:

	UBTT_MidBossmannequinSetSee();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
