// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTT_MidBossmannequinSetSee.h"
#include "CharMoveTest/FieldMonster/MidBossmannequinAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "CharMoveTest/FieldMonster/MidBossmannequin.h"

UBTT_MidBossmannequinSetSee::UBTT_MidBossmannequinSetSee()
{
	NodeName = TEXT("FindPlayer_SetSee");
}

EBTNodeResult::Type UBTT_MidBossmannequinSetSee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMidBossmannequinAIController::IsSeeKey, true);

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UBTT_MidBossmannequinSetSee::SetSeeTimer, &OwnerComp, EBTNodeResult::Succeeded);
	float TimerDelay = 1.0f;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, TimerDelay, false);


	return EBTNodeResult::InProgress;

}

void UBTT_MidBossmannequinSetSee::SetSeeTimer(UBehaviorTreeComponent* OwnerComp, EBTNodeResult::Type TaskResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Set See Timer"));
	OwnerComp->RequestExecution(TaskResult);
}
