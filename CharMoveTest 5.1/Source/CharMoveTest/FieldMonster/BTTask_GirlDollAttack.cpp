// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTTask_GirlDollAttack.h"
#include "CharMoveTest/FieldMonster/GirlDollAIController.h"
#include "CharMoveTest/FieldMonster/GirlDoll.h"


UBTTask_GirlDollAttack::UBTTask_GirlDollAttack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

EBTNodeResult::Type UBTTask_GirlDollAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto GirlDoll = Cast<AGirlDoll>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == GirlDoll)
		return EBTNodeResult::Failed;

	GirlDoll->Attack_Melee();
	IsAttacking = true;
	GirlDoll->OnAttackEnd.AddLambda([this]() -> void {
		IsAttacking = false;
	});
	

		return EBTNodeResult::InProgress;
	//return EBTNodeResult::Type();
}

void UBTTask_GirlDollAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSecondes);

	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}


	//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	
}
