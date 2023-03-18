// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/FindPlayer_BTTaskNode.h"

UFindPlayer_BTTaskNode::UFindPlayer_BTTaskNode() /* : moveSpeed(1000.0f) */
{
	NodeName = TEXT("FindPlayer_SetSee");
}

EBTNodeResult::Type UFindPlayer_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::see, true);

	return EBTNodeResult::Succeeded;
}