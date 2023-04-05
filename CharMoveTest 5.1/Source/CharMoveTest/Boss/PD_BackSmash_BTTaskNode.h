// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CharMoveTest/Boss/Boss_BlackBoardKey.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CharMoveTest/Boss/PD_RightArm.h"
#include "CharMoveTest/Boss/PD_LeftArm.h"
#include "PD_BackSmash_BTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UPD_BackSmash_BTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
private:
	UPD_BackSmash_BTTaskNode();

	float RandomValue;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	APD_LeftArm* LArm;
	APD_RightArm* RArm;
};
