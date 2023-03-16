// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/SetRotaiton_BTTaskNode.h"

USetRotaiton_BTTaskNode::USetRotaiton_BTTaskNode()
{
	NodeName = TEXT("Set Rotaiton");
}

EBTNodeResult::Type USetRotaiton_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Self = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey::selfActor));

	OwnerComp.GetBlackboardComponent()->SetValueAsRotator(bossKey::preRotation, Self->GetActorRotation());
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::setRotation, true);

	return EBTNodeResult::Succeeded;
}