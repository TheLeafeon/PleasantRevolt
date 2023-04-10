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
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(bossKey::enemyActor, PlayerCharacter); //블랙보드에 플레이어 캐릭터 변수 저장
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::inRange, true); //범위 안에 있으면 true

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
		//OwnerComp.GetBlackboardComponent()->SetValueAsObject(bossKey::enemyActor, nullptr); //없으면 null
	}
	
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::inRange, false); //범위 안에 없으면 false
	//타격판정 false로 바꿔주기
}
