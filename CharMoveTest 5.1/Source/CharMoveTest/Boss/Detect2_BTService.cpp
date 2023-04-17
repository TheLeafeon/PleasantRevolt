// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/Detect2_BTService.h"

UDetect2_BTService::UDetect2_BTService() : DetectRadius(0)
{
	NodeName = TEXT("Detect2");
	Interval = 1.0f;
}

void UDetect2_BTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::inRange2, true); //���� �ȿ� ������ true

				return;
			}
		}
	}
	else
	{
		//OwnerComp.GetBlackboardComponent()->SetValueAsObject(bossKey::enemyActor, nullptr); //������ null
	}

	//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::inRange2, false); //���� �ȿ� ������
}
