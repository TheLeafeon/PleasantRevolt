// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GirlDollAttack.h"
#include "GirlDollAIController.h"
#include "GirlDoll.h"


UBTTask_GirlDollAttack::UBTTask_GirlDollAttack()
{
	bNotifyTick = true;
	isDuringAttack = false;
}
EBTNodeResult::Type UBTTask_GirlDollAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto GirlDoll = Cast<AGirlDoll>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == GirlDoll)
		return EBTNodeResult::Failed;

	isDuringAttack = true;

	GirlDoll->Attack_Melee();
	
	
	//isDuringAttack = false;


	return EBTNodeResult::InProgress;
}
void UBTTask_GirlDollAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!isDuringAttack)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}