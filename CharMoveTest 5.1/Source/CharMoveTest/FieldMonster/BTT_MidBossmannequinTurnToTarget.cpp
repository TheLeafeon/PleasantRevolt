// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTT_MidBossmannequinTurnToTarget.h"
#include "CharMoveTest/FieldMonster/MidBossmannequinAIController.h"
#include "GameFramework/Actor.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "TimerManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTT_MidBossmannequinTurnToTarget::UBTT_MidBossmannequinTurnToTarget()
{
	NodeName = TEXT("TurnToTarget");

	TurnEnd = false;
	TurnTime = 1.0f;
	
}

EBTNodeResult::Type UBTT_MidBossmannequinTurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto MidBossmannequin = Cast<AMidBossmannequin>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == MidBossmannequin)
		return EBTNodeResult::Failed;

	auto Target = Cast<APlayerableCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMidBossmannequinAIController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - MidBossmannequin->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	MidBossmannequin->SetActorRotation(FMath::RInterpTo(MidBossmannequin->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 10.0f));


	return EBTNodeResult::Succeeded;
}
