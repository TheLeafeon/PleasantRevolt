// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PD_FallDecal_AIController.h"

APD_FallDecal_AIController::APD_FallDecal_AIController() : BlackboardComp(Blackboard)
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Boss/2Stage/PD_FallDecal_BlackboardData.PD_FallDecal_BlackboardData"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Boss/2Stage/PD_FallDecal_BehaviorTree.PD_FallDecal_BehaviorTree"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void APD_FallDecal_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


	if (UseBlackboard(BBAsset, BlackboardComp))
	{
		if (!RunBehaviorTree(BTAsset))
		{

		}
	}
}