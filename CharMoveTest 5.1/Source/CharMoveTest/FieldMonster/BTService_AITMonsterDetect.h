// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_AITMonsterDetect.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBTService_AITMonsterDetect : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_AITMonsterDetect();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
