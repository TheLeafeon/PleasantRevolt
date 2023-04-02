// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PlasticDoll_AIController.h"

APlasticDoll_AIController::APlasticDoll_AIController() : BlackboardComp(Blackboard)
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Boss/2Stage/PlasticDoll_BlackboardData.PlasticDoll_BlackboardData"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Boss/2Stage/PlasticDoll_BehaviorTree.PlasticDoll_BehaviorTree"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void APlasticDoll_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		if (!RunBehaviorTree(BTAsset))
		{

		}
	}
}
