// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTT_MidBossmannequinAttackRange.h"
#include "CharMoveTest/FieldMonster/MidBossmannequinAIController.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "BTT_MidBossmannequinAttackRange.h"

UBTT_MidBossmannequinAttackRange::UBTT_MidBossmannequinAttackRange()
{
	AttackRangeRadiusSize = 400.0f;
}

EBTNodeResult::Type UBTT_MidBossmannequinAttackRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);



	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	//AGirlDoll* ControllingGirlDoll = OwnerComp.GetPawn();
	if (nullptr == ControllingPawn) return EBTNodeResult::Failed;

	UWorld* World = ControllingPawn->GetWorld();

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMidBossmannequinAIController::RushHitKey, false);

	//공격 범위 인식
	FVector AttackRangeCenter = ControllingPawn->GetActorLocation();

	if (nullptr == World) return EBTNodeResult::Failed;
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

				return EBTNodeResult::Succeeded;
			}
		}
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMidBossmannequinAIController::InRangeKey, false); //범위 안에 있으면 true




	return EBTNodeResult::Succeeded;

}
