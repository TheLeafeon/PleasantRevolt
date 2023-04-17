// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CharMoveTest/TestMonsterArea.h"
#include "BTS_DoveDollDetect.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBTS_DoveDollDetect : public UBTService
{
	GENERATED_BODY()
public:
	UBTS_DoveDollDetect();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
