// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/BackSmash_BTTaskNode.h"

UBackSmash_BTTaskNode::UBackSmash_BTTaskNode() : RandomValue(0)
{
	NodeName = TEXT("BackSmash");
}

EBTNodeResult::Type UBackSmash_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	RandomValue = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(bossKey2::randomArm);

	if (RandomValue <= 0.5)
	{
		LArm = Cast<APD_LeftArm>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm));
		LArm->BackSmash();
	}
	else
	{
		RArm = Cast<APD_RightArm>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm));
		RArm->BackSmash();
	}

	return EBTNodeResult::Succeeded;
}