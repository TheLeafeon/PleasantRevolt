// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PD_BackSmash_BTTaskNode.h"

UPD_BackSmash_BTTaskNode::UPD_BackSmash_BTTaskNode() : RandomValue(0)
{
	NodeName = TEXT("PD BackSmash");
}

EBTNodeResult::Type UPD_BackSmash_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
