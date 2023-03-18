// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CharMoveTest/Boss/Boss_BlackBoardKey.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SetRotaiton_BTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API USetRotaiton_BTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

private:
	UPROPERTY()
	APawn* Self;

	USetRotaiton_BTTaskNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
