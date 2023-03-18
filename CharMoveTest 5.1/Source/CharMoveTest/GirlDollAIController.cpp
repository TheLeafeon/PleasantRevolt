// Fill out your copyright notice in the Description page of Project Settings.

#include "GirlDollAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AGirlDollAIController::HomePosKey(TEXT("HomePos"));
const FName AGirlDollAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AGirlDollAIController::TargetKey(TEXT("Target"));

AGirlDollAIController::AGirlDollAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/Monster/AI/BB_GirlDoll.BB_GirlDoll"));
	if (BBObject.Succeeded())
	{
		BBGirlDoll = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Monster/AI/BT_GirlDoll.BT_GirlDoll"));
	if (BTObject.Succeeded())
	{
		BTGirlDoll = BTObject.Object;
	}
}

void AGirlDollAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBGirlDoll, BlackboardComp))
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTGirlDoll))
		{

		}
	}
}

