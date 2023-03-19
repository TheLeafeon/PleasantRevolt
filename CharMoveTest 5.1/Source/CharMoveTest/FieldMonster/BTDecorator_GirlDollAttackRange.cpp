// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTDecorator_GirlDollAttackRange.h"
#include "CharMoveTest/FieldMonster/GirlDollAIController.h"
#include "CharMoveTest/TestCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"



UBTDecorator_GirlDollAttackRange::UBTDecorator_GirlDollAttackRange()
{
	NodeName = TEXT("CanAttack");
	
}

bool UBTDecorator_GirlDollAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return false;

	auto Target = Cast<ATestCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AGirlDollAIController::TargetKey));
	if (nullptr == Target)
		return false;

	bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.0f);
	return bResult;
}
