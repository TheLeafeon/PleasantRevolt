// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTDecorator_IsInAttackRange.h"
#include "CharMoveTest/FieldMonster/GirlDollAIController.h"
#include "CharMoveTest/FieldMonster/GirlDoll.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);


	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return false;

	auto Target = Cast<APlayerableCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AGirlDollAIController::TargetKey));

	if (nullptr == Target)
		return false;

	bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.0f);
	return bResult;
}
