// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PD_SmashWait_BTTaskNode.h"

UPD_SmashWait_BTTaskNode::UPD_SmashWait_BTTaskNode()
{
	NodeName = TEXT("SmashWait");
}

EBTNodeResult::Type UPD_SmashWait_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	RandomValue = FMath::RandRange(0.0f, 1.0f);

	//다음 테스크를 위해 랜덤값 저장
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(bossKey2::randomArm, RandomValue);

	if (RandomValue <= 0.5)
	{
		LArm = Cast<APD_LeftArm>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm));
		LArm->SmashWait();
	}
	else
	{
		RArm = Cast<APD_RightArm>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm));
		RArm->SmashWait();
	}
	//빨간원 생성하기

	return EBTNodeResult::Succeeded;
}