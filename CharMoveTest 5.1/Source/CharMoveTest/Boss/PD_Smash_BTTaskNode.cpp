// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PD_Smash_BTTaskNode.h"

UPD_Smash_BTTaskNode::UPD_Smash_BTTaskNode() : RandomValue(0)
{
	NodeName = TEXT("Smash");
}

EBTNodeResult::Type UPD_Smash_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm);
	//OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm);

	RandomValue = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(bossKey2::randomArm);

	if (RandomValue <= 0.5)
	{
		LArm = Cast<APD_LeftArm>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm));
		LArm->Smash();
	}
	else
	{
		RArm = Cast<APD_RightArm>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm));
		RArm->Smash();
	}

	return EBTNodeResult::Succeeded;
}