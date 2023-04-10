// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/Detect_BTService.h"

UDetect_BTService::UDetect_BTService() : DetectRadius(0)
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UDetect_BTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (nullptr == ControllingPawn)
	{
		return;
	}

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();

	if (nullptr == World)
	{
		return;
	}

	//DetectRadius�� ũ�� ��ŭ �������� ���� ��ü�� ���� ������Ʈ�� ����
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	DetectRadius = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(bossKey::detectRadius);

	//������Ʈ�� ������ �Ǹ�, �� ������Ʈ�� ĳ�������� �˻�
	if (bResult) //���� ������ ������ �ٷ� inRange�� false�� �Ǿ����� �����ٵ�
	{
		for (FOverlapResult OverlapResult : OverlapResults)
		{
			APlayerableCharacter* PlayerCharacter = Cast<APlayerableCharacter>(OverlapResult.GetActor()); //�÷��̾� ���� �ٲ�� �ٲ��� �ʿ� ����

			if (PlayerCharacter && PlayerCharacter->GetController()->IsPlayerController()) //�÷��̾� ĳ���Ͷ��?
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(bossKey::enemyActor, PlayerCharacter); //�����忡 �÷��̾� ĳ���� ���� ����
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::inRange, true); //���� �ȿ� ������ true

				/*
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, PlayerCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), PlayerCharacter->GetActorLocation(), FColor::Blue, false, 0.2f);
				*/
				return;
			}
		}
	}
	else
	{
		//OwnerComp.GetBlackboardComponent()->SetValueAsObject(bossKey::enemyActor, nullptr); //������ null
	}
	
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::inRange, false); //���� �ȿ� ������ false
	//Ÿ������ false�� �ٲ��ֱ�
}
