// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_MidBossmannequinRangeDetect.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBTS_MidBossmannequinRangeDetect : public UBTService
{
	GENERATED_BODY()
public:
	UBTS_MidBossmannequinRangeDetect();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY()
		float AttackRangeRadiusSize; //공격 인식 범위
};
