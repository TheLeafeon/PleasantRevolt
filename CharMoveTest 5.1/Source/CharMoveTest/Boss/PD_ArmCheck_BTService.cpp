// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PD_ArmCheck_BTService.h"

UPD_ArmCheck_BTService::UPD_ArmCheck_BTService()
{
	NodeName = TEXT("ArmCheck");
}

void UPD_ArmCheck_BTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm) == nullptr && OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm) == nullptr)
	{
		//3페로 넘어가기
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey2::isArmLive, false);
		return;
	}
}