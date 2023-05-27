// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTD_NearmannequinAttackRange.h"
#include "CharMoveTest/FieldMonster/NearmannequinAIController.h"
#include "CharMoveTest/FieldMonster/Nearmannequin.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_NearmannequinAttackRange::UBTD_NearmannequinAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTD_NearmannequinAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return false;

	auto Target = Cast<APlayerableCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ANearmannequinAIController::TargetKey));

	if (nullptr == Target)
		return false;

	FVector PawnForwardVector = ControllingPawn->GetActorForwardVector();
	FVector DirectionToTarget = Target->GetActorLocation() - ControllingPawn->GetActorLocation();
	float DotProduct = FVector::DotProduct(PawnForwardVector, DirectionToTarget);
	bResult = (DotProduct > 0.0f && Target->GetDistanceTo(ControllingPawn) <= 150.0f);

	return bResult;
}
