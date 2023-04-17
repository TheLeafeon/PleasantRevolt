// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTT_DoveDollAttack.h"
#include "CharMoveTest/FieldMonster/DoveDollAIController.h"
#include "CharMoveTest/FieldMonster/DoveDoll.h"

UBTT_DoveDollAttack::UBTT_DoveDollAttack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTT_DoveDollAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto DoveDoll = Cast<ADoveDoll>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == DoveDoll)
		return EBTNodeResult::Failed;

	
	DoveDoll->Attack();
	IsAttacking = true;

	DoveDoll->DoveDollOnAttackEnd.AddLambda([this]()->void {
		IsAttacking = false;
	});


	return EBTNodeResult::InProgress;
}

void UBTT_DoveDollAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSecondes);

	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
