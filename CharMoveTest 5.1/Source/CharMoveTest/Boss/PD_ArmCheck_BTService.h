// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/Boss/Boss_BlackBoardKey.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTService.h"
#include "PD_ArmCheck_BTService.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UPD_ArmCheck_BTService : public UBTService
{
	GENERATED_BODY()

private:
	UPD_ArmCheck_BTService();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
