// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTT_MidBossmannequinAttack.h"
#include "CharMoveTest/FieldMonster/MidBossmannequinAIController.h"
#include "CharMoveTest/FieldMonster/MidBossmannequin.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_MidBossmannequinAttack::UBTT_MidBossmannequinAttack()
{
	bNotifyTick = true;
	IsAttacking = false;
	//false 멀경우 , true 가까울경우
	InRange = false;
}

EBTNodeResult::Type UBTT_MidBossmannequinAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	InRange= OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMidBossmannequinAIController::InRangeKey);

	auto MidBossmannequin = Cast<AMidBossmannequin>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == MidBossmannequin)
		return EBTNodeResult::Failed;

	if (!InRange)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("OutRange"));
		MidBossmannequin->OutRangeAttack();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("InRange"));
		MidBossmannequin->InRangeAttack();
	}




	return EBTNodeResult::InProgress;
}

void UBTT_MidBossmannequinAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecondes)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSecondes);

	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
