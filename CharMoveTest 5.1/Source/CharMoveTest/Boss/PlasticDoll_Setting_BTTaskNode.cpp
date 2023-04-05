// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PlasticDoll_Setting_BTTaskNode.h"

UPlasticDoll_Setting_BTTaskNode::UPlasticDoll_Setting_BTTaskNode()
{
	NodeName = TEXT("PD Set Key");
}

EBTNodeResult::Type UPlasticDoll_Setting_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(bossKey2::player, PlayerPawn);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey2::keyTrue, true);

	return EBTNodeResult::Succeeded;
}
