// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTTask_DragonDollAttack.h"
#include "CharMoveTest/FieldMonster/DragonDollAIController.h"
#include "CharMoveTest/FieldMonster/DragonDoll.h"

UBTTask_DragonDollAttack::UBTTask_DragonDollAttack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_DragonDollAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto DragonDoll = Cast<ADragonDoll>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == DragonDoll)
		return EBTNodeResult::Failed;

	DragonDoll->Attack_Melee();
	IsAttacking = true;

	DragonDoll->DragonDollOnAttackEnd.AddLambda([this]()->void {
		IsAttacking = false;
	});


	return EBTNodeResult::InProgress;
	return EBTNodeResult::Type();
}

void UBTTask_DragonDollAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSecondes);

	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}


