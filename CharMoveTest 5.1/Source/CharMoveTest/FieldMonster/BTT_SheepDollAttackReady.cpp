// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTT_SheepDollAttackReady.h"
#include "CharMoveTest/FieldMonster/SheepDollAIController.h"
#include "CharMoveTest/FieldMonster/SheepDoll.h"
#include "BTT_SheepDollAttackReady.h"

UBTT_SheepDollAttackReady::UBTT_SheepDollAttackReady()
{
	NodeName = TEXT("SheepDollAttackReady");

	bNotifyTick = true;
	IsAttackReady = false;
}

EBTNodeResult::Type UBTT_SheepDollAttackReady::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto SheepDoll = Cast<ASheepDoll>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == SheepDoll)
		return EBTNodeResult::Failed;

	SheepDoll->Rush_Ready();
	IsAttackReady = true;

	SheepDoll->SheepDollOnAttackReadyEnd.AddLambda([this]() -> void {
		IsAttackReady = false;
	});



	return EBTNodeResult::InProgress;
}

void UBTT_SheepDollAttackReady::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSecondes);

	if (!IsAttackReady)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
