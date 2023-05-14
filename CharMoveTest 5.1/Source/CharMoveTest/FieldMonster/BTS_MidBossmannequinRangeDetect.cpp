// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTS_MidBossmannequinRangeDetect.h"
#include "CharMoveTest/FieldMonster/MidBossmannequinAIController.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTS_MidBossmannequinRangeDetect::UBTS_MidBossmannequinRangeDetect()
{
	NodeName = TEXT("AttackRangeDetect");
	Interval = 1.0f;

	AttackRangeRadiusSize = 400.0f;
}

void UBTS_MidBossmannequinRangeDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	//AGirlDoll* ControllingGirlDoll = OwnerComp.GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();

	//공격 범위 인식
	FVector AttackRangeCenter = ControllingPawn->GetActorLocation();

	if (nullptr == World) return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);

	bool AttackRangebResult = World->OverlapMultiByChannel(
		OverlapResults,
		AttackRangeCenter,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRangeRadiusSize),
		CollisionQueryParam
	);

	if (AttackRangebResult) //범위 밖으로 나가면 바로 inRange가 false가 되었으면 좋을텐데
	{
		for (FOverlapResult OverlapResult : OverlapResults)
		{
			APlayerableCharacter* PlayerCharacter = Cast<APlayerableCharacter>(OverlapResult.GetActor()); //플레이어 파일 바뀌면 바꿔줄 필요 있음

			if (PlayerCharacter && PlayerCharacter->GetController()->IsPlayerController()) //플레이어 캐릭터라면?
			{

				OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMidBossmannequinAIController::InRangeKey, true); //범위 안에 있으면 true

				return;
			}
		}
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMidBossmannequinAIController::InRangeKey, false); //범위 안에 있으면 true
}
