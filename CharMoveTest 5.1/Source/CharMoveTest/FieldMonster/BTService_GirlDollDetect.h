// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CharMoveTest/FieldMonster/GirlDoll.h"
#include "BTService_GirlDollDetect.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBTService_GirlDollDetect : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_GirlDollDetect();

	
	AGirlDoll* MyGirlDoll;


protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;



};
