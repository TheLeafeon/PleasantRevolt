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

	//���� ���� �ν�
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

	if (AttackRangebResult) //���� ������ ������ �ٷ� inRange�� false�� �Ǿ����� �����ٵ�
	{
		for (FOverlapResult OverlapResult : OverlapResults)
		{
			APlayerableCharacter* PlayerCharacter = Cast<APlayerableCharacter>(OverlapResult.GetActor()); //�÷��̾� ���� �ٲ�� �ٲ��� �ʿ� ����

			if (PlayerCharacter && PlayerCharacter->GetController()->IsPlayerController()) //�÷��̾� ĳ���Ͷ��?
			{

				OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMidBossmannequinAIController::InRangeKey, true); //���� �ȿ� ������ true

				return EBTNodeResult::Succeeded;
			}
		}
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMidBossmannequinAIController::InRangeKey, false); //���� �ȿ� ������ true




	return EBTNodeResult::Succeeded;

}
