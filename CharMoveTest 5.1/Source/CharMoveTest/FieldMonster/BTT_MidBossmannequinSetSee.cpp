// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTT_MidBossmannequinSetSee.h"
#include "CharMoveTest/FieldMonster/MidBossmannequinAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "CharMoveTest/FieldMonster/MidBossmannequin.h"

UBTT_MidBossmannequinSetSee::UBTT_MidBossmannequinSetSee()
{
	NodeName = TEXT("FindPlayer_SetSee");
}

EBTNodeResult::Type UBTT_MidBossmannequinSetSee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMidBossmannequinAIController::IsSeeKey, true);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(AMidBossmannequinAIController::LastTargetLocationKey, BlackboardComp->GetValueAsVector("TargetLocation"));
	
	

	return EBTNodeResult::Succeeded;

}

