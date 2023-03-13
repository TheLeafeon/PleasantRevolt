// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/FindPlayer_BTTaskNode.h"

UFindPlayer_BTTaskNode::UFindPlayer_BTTaskNode() /* : moveSpeed(1000.0f) */
{
	NodeName = TEXT("FindPlayer_SetSee");
}

EBTNodeResult::Type UFindPlayer_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Controller = Cast<ABossAIController>(OwnerComp.GetAIOwner());
	auto Boss = Controller->GetPawn();

	if (nullptr == Boss)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Boss Initialize faild!"));
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (nullptr == NavSystem)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Boss in Navi"));
		return EBTNodeResult::Failed;
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::see, true);

	return EBTNodeResult::Succeeded;
}