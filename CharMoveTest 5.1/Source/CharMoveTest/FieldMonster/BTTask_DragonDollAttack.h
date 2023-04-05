// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DragonDollAttack.generated.h"

/**
 *
 */
UCLASS()
class CHARMOVETEST_API UBTTask_DragonDollAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_DragonDollAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes) override;

private:
	bool IsAttacking = false;

};
