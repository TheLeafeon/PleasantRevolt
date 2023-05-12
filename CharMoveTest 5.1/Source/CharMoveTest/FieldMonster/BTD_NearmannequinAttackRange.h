// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_NearmannequinAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBTD_NearmannequinAttackRange : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTD_NearmannequinAttackRange();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)const override;

};
