// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PD_BackSmash_BTTaskNode.h"

UPD_BackSmash_BTTaskNode::UPD_BackSmash_BTTaskNode() : RandomValue(0)
{
	NodeName = TEXT("BackSmash");
}

EBTNodeResult::Type UPD_BackSmash_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	RandomValue = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(bossKey2::randomArm);

	if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm) == nullptr && OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm) == nullptr)
	{
		//3페로 넘어가기
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey2::isArmLive, false);

		return EBTNodeResult::Succeeded;
	}
	else if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm) == nullptr)
	{
		//RandomValue = 0.6;
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey2::isLeftArm, false);
	}
	else if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm) == nullptr)
	{
		//RandomValue = 0.1;
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey2::isLeftArm, true);
	}

	if (RandomValue <= 0.5 && OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm) != nullptr)
	{
		LArm = Cast<APD_LeftArm>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm));
		LArm->BackSmash();
	}
	else if (RandomValue > 0.5 && OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm) != nullptr)
	{
		RArm = Cast<APD_RightArm>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm));
		RArm->BackSmash();
	}

	return EBTNodeResult::Succeeded;
}
