// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTD_MiniMouseDollAttackRange.h"
#include "CharMoveTest/FieldMonster/MouseDollAIController.h"
#include "CharMoveTest/FieldMonster/MouseDoll.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_MiniMouseDollAttackRange::UBTD_MiniMouseDollAttackRange()
{
	NodeName = TEXT("MiniMouseDollCanAttack");
}

bool UBTD_MiniMouseDollAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);


	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return false;

	auto Target = Cast<APlayerableCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMouseDollAIController::TargetKey));

	if (nullptr == Target)
		return false;



	FVector PawnForwardVector = ControllingPawn->GetActorForwardVector();
	FVector DirectionToTarget = Target->GetActorLocation() - ControllingPawn->GetActorLocation();
	float DotProduct = FVector::DotProduct(PawnForwardVector, DirectionToTarget);
	bResult = (DotProduct > 0.0f && Target->GetDistanceTo(ControllingPawn) <= 200.0f);

	return bResult;

}
