// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/BossAIController.h"

ABossAIController::ABossAIController() : BlackboardComp(Blackboard)
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/Boss/1Stage/BearDoll_BlackboardData.BearDoll_BlackboardData"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Boss/1Stage/BearDoll_BehaviorTree.BearDoll_BehaviorTree"));
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

void ABossAIController::PauseBehaviorTree()
{
	SetActorTickEnabled(false); //비헤이비어 트리를 중지
}

void ABossAIController::ResumeBehaviorTree()
{
	SetActorTickEnabled(true); //비헤이비어 트리를 다시 실행
}

void ABossAIController::SetEnemy(AActor* enemy)
{
	BlackboardComp->SetValueAsObject(bossKey::enemyActor, enemy);
}

void ABossAIController::SetStop(bool stop)
{
	BlackboardComp->SetValueAsBool(bossKey::keyStop, stop);
	BlackboardComp->SetValueAsBool(bossKey::see, stop);
}