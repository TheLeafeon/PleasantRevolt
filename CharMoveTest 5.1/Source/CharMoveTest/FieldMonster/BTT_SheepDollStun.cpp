// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTT_SheepDollStun.h"
#include "CharMoveTest/FieldMonster/SheepDollAIController.h"
#include "CharMoveTest/FieldMonster/SheepDoll.h"

UBTT_SheepDollStun::UBTT_SheepDollStun()
{
	NodeName = TEXT("SheepDollStun");

	bNotifyTick = true;
	IsStun = false;
}

EBTNodeResult::Type UBTT_SheepDollStun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto SheepDoll = Cast<ASheepDoll>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == SheepDoll)
		return EBTNodeResult::Failed;

	SheepDoll->Stun();
	IsStun = true;

	SheepDoll->SheepDollStunEnd.AddLambda([this]() -> void {
		IsStun = false;
	});



	return EBTNodeResult::InProgress;
}

void UBTT_SheepDollStun::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSecondes);

	if (!IsStun)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
