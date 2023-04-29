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
	�𸮾�4������ UBlacboardComponent* Blackboard;
	�𸮾�5������ TObjectPtr<UBlackboardComponent> Blackboard;�̱� ������
	UBlackboardComponent* BlackboardComp = Blackboard; �� �����.
	*/
	{
		if (!RunBehaviorTree(BTAsset))
		{

		}
	}
}

void ABossAIController::PauseBehaviorTree()
{
	SetActorTickEnabled(false); //�����̺�� Ʈ���� ����
}

void ABossAIController::ResumeBehaviorTree()
{
	SetActorTickEnabled(true); //�����̺�� Ʈ���� �ٽ� ����
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