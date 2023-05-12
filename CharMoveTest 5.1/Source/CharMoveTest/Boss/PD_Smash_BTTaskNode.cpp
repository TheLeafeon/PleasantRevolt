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

	if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm) == nullptr && OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm) == nullptr)
	{
		//3페로 넘어가기
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey2::isArmLive, false);

		return EBTNodeResult::Succeeded;
	}
	else if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm) == nullptr)
	{
		RandomValue = 0.6;
		//return EBTNodeResult::Succeeded;
	}
	else if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm) == nullptr)
	{
		RandomValue = 0.1;
		//return EBTNodeResult::Succeeded;
	}

	if (RandomValue <= 0.5 && OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm) != nullptr)
	{
		LArm = Cast<APD_LeftArm>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm));
		LArm->Smash();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("?"));
	}
	else if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm) != nullptr)
	{
		RArm = Cast<APD_RightArm>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm));
		RArm->Smash();
	}

	return EBTNodeResult::Succeeded;
}