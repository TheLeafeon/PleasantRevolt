// Fill out your copyright notice in the Description page of Project Settings.


#include "DragonDollAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ADragonDollAIController::HomePosKey(TEXT("HomePos"));
const FName ADragonDollAIController::TargetKey(TEXT("Target"));

ADragonDollAIController::ADragonDollAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/Monster/AI/BB_DragonDoll.BB_DragonDoll"));
	if (BBObject.Succeeded())
	{
		BBDragonDoll = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Monster/AI/BT_DragonDoll.BT_DragonDoll"));
	if (BTObject.Succeeded())
	{
		BTDragonDoll = BTObject.Object;
	}


}

void ADragonDollAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBDragonDoll, BlackboardComp))
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTDragonDoll))
		{

		}
	}
}