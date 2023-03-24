// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/AITMonsterAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AITMonsterAIController.h"

const FName AAITMonsterAIController::HomePosKey(TEXT("HomePos"));
const FName AAITMonsterAIController::TargetKey(TEXT("Target"));


AAITMonsterAIController::AAITMonsterAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/Monster/AI/BB_AITMonster.BB_AITMonster"));
	if (BBObject.Succeeded())
	{
		BBAITMonster = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Monster/AI/BT_AITMonster.BT_AITMonster"));
	if (BTObject.Succeeded())
	{
		BTAITMonster = BTObject.Object;
	}

}

void AAITMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBAITMonster, BlackboardComp))
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAITMonster))
		{

		}
	}
}
