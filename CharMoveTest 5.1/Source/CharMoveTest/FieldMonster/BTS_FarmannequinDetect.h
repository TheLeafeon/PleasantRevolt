// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_FarmannequinDetect.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBTS_FarmannequinDetect : public UBTService
{
	GENERATED_BODY()
public:
	UBTS_FarmannequinDetect();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
};
