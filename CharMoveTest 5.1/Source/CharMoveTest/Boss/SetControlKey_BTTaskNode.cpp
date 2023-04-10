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
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(bossKey::enemyActor, PlayerPawn);
	BossAIGISS = UGameInstance::GetSubsystem<UBossAI_GameInstanceSubsystem>(GetWorld()->GetGameInstance());
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(bossKey::detectRadius, BossAIGISS->Control_DetectRadius);
	//OwnerComp.GetBlackboardComponent()->SetValueAsFloat(bossKey::rushSpeed, BossAIGISS->BearDoll_RushSpeed);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::setting, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::keyTrue, true);
	//OwnerComp.GetBlackboardComponent()->SetValueAsRotator(bossKey::x360, FRotator(350, 0, 0));
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::inRange, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::isRotate, false);

	return EBTNodeResult::Succeeded;
}
