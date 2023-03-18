// Fill out your copyright notice in the Description page of Project Settings.


#include "RabbitDollAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ARabbitDollAIController::HomePosKey(TEXT("HomePos"));
const FName ARabbitDollAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ARabbitDollAIController::TargetKey(TEXT("Target"));


ARabbitDollAIController::ARabbitDollAIController()
{

	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/Monster/AI/BB_RabbitDoll.BB_RabbitDoll"));
	if (BBObject.Succeeded())
	{
		BBRabbitDoll = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Monster/AI/BT_RabbitDoll.BT_RabbitDoll"));
	if (BTObject.Succeeded())
	{
		BTRabbitDoll = BTObject.Object;
	}
}

void ARabbitDollAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBRabbitDoll, BlackboardComp))
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTRabbitDoll))
		{

		}
	}
}
