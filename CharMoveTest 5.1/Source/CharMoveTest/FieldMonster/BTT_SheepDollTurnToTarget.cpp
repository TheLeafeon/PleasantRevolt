// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTT_SheepDollTurnToTarget.h"
#include "CharMoveTest/FieldMonster/SheepDollAIController.h"
#include "GameFramework/Actor.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "TimerManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTT_SheepDollTurnToTarget::UBTT_SheepDollTurnToTarget()
{
	
	NodeName = TEXT("TurnToTarget");
	StartTime = 0;
}

EBTNodeResult::Type UBTT_SheepDollTurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	/*auto SheepDoll = Cast<ASheepDoll>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == SheepDoll)
		return EBTNodeResult::Failed;

	auto Target = Cast<APlayerableCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ASheepDollAIController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;


	FVector LookVector = Target->GetActorLocation() - SheepDoll->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	SheepDoll->SetActorRotation(FMath::RInterpTo(SheepDoll->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 10.0f));

	OwnerComp.DelayExecution(this, NodeMemory, 0.1f);


	return EBTNodeResult::Succeeded;*/
	auto SheepDoll = Cast<ASheepDoll>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == SheepDoll)
		return EBTNodeResult::Failed;

	auto Target = Cast<APlayerableCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ASheepDollAIController::TargetKey));
	if (nullptr == Target)
		return EBTNodeResult::Failed;

	StartTime = GetWorld()->GetTimeSeconds();

	return EBTNodeResult::InProgress;
}

void UBTT_SheepDollTurnToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto SheepDoll = Cast<ASheepDoll>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == SheepDoll)
		return;

	auto Target = Cast<APlayerableCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ASheepDollAIController::TargetKey));
	if (nullptr == Target)
		return;

	FVector LookVector = Target->GetActorLocation() - SheepDoll->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	SheepDoll->SetActorRotation(FMath::RInterpTo(SheepDoll->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 10.0f));

	/*if (GetWorld()->GetTimeSeconds() >= StartTime + 2.0f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}*/

}






