// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTT_NearmannequinAttack.h"
#include "CharMoveTest/FieldMonster/NearmannequinAIController.h"
#include "CharMoveTest/FieldMonster/Nearmannequin.h"

UBTT_NearmannequinAttack::UBTT_NearmannequinAttack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTT_NearmannequinAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Nearmannequin = Cast<ANearmannequin>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Nearmannequin)
		return EBTNodeResult::Failed;

	Nearmannequin->Attack_Ready();
	IsAttacking = true;

	Nearmannequin->NearmannequinOnAttackEnd.AddLambda([this]() -> void {
		IsAttacking = false;
	});


	return EBTNodeResult::InProgress;
}

void UBTT_NearmannequinAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSecondes);

	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
