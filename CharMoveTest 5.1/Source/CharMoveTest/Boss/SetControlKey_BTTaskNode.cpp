// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/SetControlKey_BTTaskNode.h"
#include "Kismet/GameplayStatics.h"

USetControlKey_BTTaskNode::USetControlKey_BTTaskNode()
{
	NodeName = TEXT("Set Key");
}

EBTNodeResult::Type USetControlKey_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(bossKey2::player, PlayerPawn);

	return EBTNodeResult::Succeeded;
}
