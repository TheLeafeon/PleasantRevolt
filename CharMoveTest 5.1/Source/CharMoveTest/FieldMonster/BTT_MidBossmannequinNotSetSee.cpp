// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTT_MidBossmannequinNotSetSee.h"
#include "CharMoveTest/FieldMonster/MidBossmannequinAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CharMoveTest/FieldMonster/MidBossmannequin.h"

UBTT_MidBossmannequinNotSetSee::UBTT_MidBossmannequinNotSetSee()
{
	NodeName = TEXT("FindPlayer_NotSetSee");
}

EBTNodeResult::Type UBTT_MidBossmannequinNotSetSee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMidBossmannequinAIController::IsSeeKey, false);

	return EBTNodeResult::Succeeded;
}
