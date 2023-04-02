// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CharMoveTest/Boss/Boss_BlackBoardKey.h"
#include "PlasticDoll_Setting_BTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UPlasticDoll_Setting_BTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	UPlasticDoll_Setting_BTTaskNode();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
