// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_SheepDollAttack.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBTT_SheepDollAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_SheepDollAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes) override;

private:
	bool IsAttacking = false;

	
};
