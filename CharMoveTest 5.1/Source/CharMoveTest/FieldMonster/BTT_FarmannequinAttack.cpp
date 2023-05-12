// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTT_FarmannequinAttack.h"
#include "CharMoveTest/FieldMonster/FarmannequinAIController.h"
#include "CharMoveTest/FieldMonster/Farmannequin.h"

UBTT_FarmannequinAttack::UBTT_FarmannequinAttack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTT_FarmannequinAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Farmannequin = Cast<AFarmannequin>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Farmannequin)
		return EBTNodeResult::Failed;


	Farmannequin->Attack();
	IsAttacking = true;

	Farmannequin->FarmannequinOnAttackEnd.AddLambda([this]()->void {
		IsAttacking = false;
	});


	return EBTNodeResult::InProgress;
}

void UBTT_FarmannequinAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSecondes);

	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
