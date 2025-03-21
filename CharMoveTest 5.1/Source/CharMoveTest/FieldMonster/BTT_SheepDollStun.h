// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_SheepDollStun.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBTT_SheepDollStun : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_SheepDollStun();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes) override;

private:
	bool IsStun = false;
	
};
