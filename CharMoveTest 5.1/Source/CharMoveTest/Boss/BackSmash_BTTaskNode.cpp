// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/BackSmash_BTTaskNode.h"

UBackSmash_BTTaskNode::UBackSmash_BTTaskNode() : RandomValue(0)
{
	NodeName = TEXT("BackSmash");
}

EBTNodeResult::Type UBackSmash_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm) == nullptr && OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm) == nullptr)
	{
		//3페로 넘어가기
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey2::isArmLive, false);

		return EBTNodeResult::Failed;
	}
	else if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm) == nullptr)
	{
		RandomValue = 0.6;
	}
	else if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm) == nullptr)
	{
		RandomValue = 0.1;
	}

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