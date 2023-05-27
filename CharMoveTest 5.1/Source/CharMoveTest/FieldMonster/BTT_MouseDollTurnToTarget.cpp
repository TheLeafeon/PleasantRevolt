// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTT_MouseDollTurnToTarget.h"
#include "CharMoveTest/FieldMonster/MouseDollAIController.h"
#include "GameFramework/Actor.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "TimerManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTT_MouseDollTurnToTarget::UBTT_MouseDollTurnToTarget()
{
	NodeName = TEXT("TurnToTarget");
	StartTime = 0;
}

EBTNodeResult::Type UBTT_MouseDollTurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto MouseDoll = Cast<AMouseDoll>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == MouseDoll)
		return EBTNodeResult::Failed;

	auto Target = Cast<APlayerableCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMouseDollAIController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - MouseDoll->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	MouseDoll->SetActorRotation(FMath::RInterpTo(MouseDoll->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 10.0f));

	return EBTNodeResult::Succeeded;
}

void UBTT_MouseDollTurnToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto MouseDoll = Cast<AMouseDoll>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == MouseDoll)
		return;

	auto Target = Cast<APlayerableCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMouseDollAIController::TargetKey));
	if (nullptr == Target)
		return;

	FVector LookVector = Target->GetActorLocation() - MouseDoll->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	MouseDoll->SetActorRotation(FMath::RInterpTo(MouseDoll->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 10.0f));
}
