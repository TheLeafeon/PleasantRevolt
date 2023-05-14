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

	//���� ���� �ν�
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

	if (AttackRangebResult) //���� ������ ������ �ٷ� inRange�� false�� �Ǿ����� �����ٵ�
	{
		for (FOverlapResult OverlapResult : OverlapResults)
		{
			APlayerableCharacter* PlayerCharacter = Cast<APlayerableCharacter>(OverlapResult.GetActor()); //�÷��̾� ���� �ٲ�� �ٲ��� �ʿ� ����

			if (PlayerCharacter && PlayerCharacter->GetController()->IsPlayerController()) //�÷��̾� ĳ���Ͷ��?
			{

				OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMidBossmannequinAIController::InRangeKey, true); //���� �ȿ� ������ true

				return;
			}
		}
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMidBossmannequinAIController::InRangeKey, false); //���� �ȿ� ������ true
}
