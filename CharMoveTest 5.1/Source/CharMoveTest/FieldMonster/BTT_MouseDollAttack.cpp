// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTT_MouseDollAttack.h"
#include "CharMoveTest/FieldMonster/MouseDollAIController.h"
#include "CharMoveTest/FieldMonster/MouseDoll.h"

UBTT_MouseDollAttack::UBTT_MouseDollAttack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTT_MouseDollAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto MouseDoll = Cast<AMouseDoll>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == MouseDoll)
		return EBTNodeResult::Failed;

	MouseDoll->Attack_Ready();
	IsAttacking = true;

	MouseDoll->MouseDollOnAttackEnd.AddLambda([this]() -> void {
		IsAttacking = false;
	});


	return EBTNodeResult::InProgress;
}

void UBTT_MouseDollAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSecondes);

	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
