// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/SetControlKey_BTTaskNode.h"

USetControlKey_BTTaskNode::USetControlKey_BTTaskNode()
{
	NodeName = TEXT("Set Key");
}

EBTNodeResult::Type USetControlKey_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	BossAIGISS = UGameInstance::GetSubsystem<UBossAI_GameInstanceSubsystem>(GetWorld()->GetGameInstance());
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(bossKey::detectRadius, BossAIGISS->Control_DetectRadius);
	//OwnerComp.GetBlackboardComponent()->SetValueAsFloat(bossKey::rushSpeed, BossAIGISS->BearDoll_RushSpeed);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::setting, true);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::keyTrue, true);

	return EBTNodeResult::Succeeded;
}
