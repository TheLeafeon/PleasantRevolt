// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTT_SheepDollNotSetSee.h"
#include "CharMoveTest/FieldMonster/SheepDollAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CharMoveTest/FieldMonster/SheepDoll.h"

UBTT_SheepDollNotSetSee::UBTT_SheepDollNotSetSee()
{
	NodeName = TEXT("FindPlayer_NotSetSee");
}

EBTNodeResult::Type UBTT_SheepDollNotSetSee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(ASheepDollAIController::SeeKey, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(ASheepDollAIController::StunKey, false);


	return EBTNodeResult::Succeeded;
}
