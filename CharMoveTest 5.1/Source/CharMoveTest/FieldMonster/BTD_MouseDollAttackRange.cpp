// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTD_MouseDollAttackRange.h"
#include "CharMoveTest/FieldMonster/MouseDollAIController.h"
#include "CharMoveTest/FieldMonster/MouseDoll.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_MouseDollAttackRange::UBTD_MouseDollAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTD_MouseDollAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);


	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return false;

	auto Target = Cast<APlayerableCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMouseDollAIController::TargetKey));

	if (nullptr == Target)
		return false;

	bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.0f);
	return bResult;
}
