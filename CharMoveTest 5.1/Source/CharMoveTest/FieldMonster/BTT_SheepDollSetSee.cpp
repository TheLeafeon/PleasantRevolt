// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTT_SheepDollSetSee.h"
#include "CharMoveTest/FieldMonster/SheepDollAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CharMoveTest/FieldMonster/SheepDoll.h"

UBTT_SheepDollSetSee::UBTT_SheepDollSetSee()
{
	NodeName = TEXT("FindPlayer_SetSee");
}

EBTNodeResult::Type UBTT_SheepDollSetSee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(ASheepDollAIController::SeeKey, true);

	return EBTNodeResult::Succeeded;
}
