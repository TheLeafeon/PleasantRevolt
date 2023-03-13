// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/BossAIController.h"

ABossAIController::ABossAIController() : BlackboardComp(Blackboard)
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Boss/BearDoll_BlackboardData.BearDoll_BlackboardData"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Boss/BearDoll_BehaviorTree.BearDoll_BehaviorTree"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void ABossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	
	if (UseBlackboard(BBAsset, BlackboardComp))
	/*
	언리얼4에서는 UBlacboardComponent* Blackboard;
	언리얼5에서는 TObjectPtr<UBlackboardComponent> Blackboard;이기 때문에
	UBlackboardComponent* BlackboardComp = Blackboard; 를 해줬다.
	*/
	{
		if (!RunBehaviorTree(BTAsset))
		{

		}
	}
}