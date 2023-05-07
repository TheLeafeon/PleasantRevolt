// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PD_3Phase_Collapse_BTTaskNode.h"

UPD_3Phase_Collapse_BTTaskNode::UPD_3Phase_Collapse_BTTaskNode()
{
	NodeName = TEXT("Collapse");
}

EBTNodeResult::Type UPD_3Phase_Collapse_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	return EBTNodeResult::Succeeded;
}