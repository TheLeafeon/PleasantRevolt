// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_NearmannequinDetect.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBTS_NearmannequinDetect : public UBTService
{
	GENERATED_BODY()
public:
	UBTS_NearmannequinDetect();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
