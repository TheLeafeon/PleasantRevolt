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

	//DetectRadius의 크기 만큼 반지름을 가진 구체를 만들어서 오브젝트를 감지
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

	//오브젝트가 감지가 되면, 그 오브젝트가 캐릭터인지 검사
	if (bResult) //범위 밖으로 나가면 바로 inRange가 false가 되었으면 좋을텐데
	{
		for (FOverlapResult OverlapResult : OverlapResults)
		{
			APlayerableCharacter* PlayerCharacter = Cast<APlayerableCharacter>(OverlapResult.GetActor()); //플레이어 파일 바뀌면 바꿔줄 필요 있음

			if (PlayerCharacter && PlayerCharacter->GetController()->IsPlayerController()) //플레이어 캐릭터라면?
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::inRange2, true); //범위 안에 있으면 true

				return;
			}
		}
	}
	else
	{
		//OwnerComp.GetBlackboardComponent()->SetValueAsObject(bossKey::enemyActor, nullptr); //없으면 null
	}

	//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::inRange2, false); //범위 안에 없으면
}
