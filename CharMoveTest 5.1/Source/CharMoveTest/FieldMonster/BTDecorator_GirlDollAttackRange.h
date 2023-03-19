// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_GirlDollAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBTDecorator_GirlDollAttackRange : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_GirlDollAttackRange();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
