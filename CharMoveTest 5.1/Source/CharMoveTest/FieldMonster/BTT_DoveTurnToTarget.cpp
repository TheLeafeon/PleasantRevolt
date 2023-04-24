// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTT_DoveTurnToTarget.h"
#include "CharMoveTest/FieldMonster/DoveDollAIController.h"
#include "GameFramework/Actor.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "TimerManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTT_DoveTurnToTarget::UBTT_DoveTurnToTarget()
{
	NodeName = TEXT("TurnToTarget");
	StartTime = 0;
}

EBTNodeResult::Type UBTT_DoveTurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto DoveDoll = Cast<ADoveDoll>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == DoveDoll)
		return EBTNodeResult::Failed;

	auto Target = Cast<APlayerableCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADoveDollAIController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - DoveDoll->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	DoveDoll->SetActorRotation(FMath::RInterpTo(DoveDoll->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 10.0f));

	return EBTNodeResult::Succeeded;
}

void UBTT_DoveTurnToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto DoveDoll = Cast<ADoveDoll>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == DoveDoll)
		return;

	auto Target = Cast<APlayerableCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ADoveDollAIController::TargetKey));
	if (nullptr == Target)
		return;

	FVector LookVector = Target->GetActorLocation() - DoveDoll->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	DoveDoll->SetActorRotation(FMath::RInterpTo(DoveDoll->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 10.0f));
}
