// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTTask_MoveTo_GirlDollIsSearch.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CharMoveTest/FieldMonster/GirlDollAIController.h"
#include "Engine/TargetPoint.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"





UBTTask_MoveTo_GirlDollIsSearch::UBTTask_MoveTo_GirlDollIsSearch()
{
	NodeName = "Search";
}

EBTNodeResult::Type UBTTask_MoveTo_GirlDollIsSearch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}
