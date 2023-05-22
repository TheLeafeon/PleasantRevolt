// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTS_MidBossmannequinDetect.h"
#include "CharMoveTest/FieldMonster/MidBossmannequinAIController.h"
#include "CharMoveTest/FieldMonster/MidBossmannequin.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTS_MidBossmannequinDetect::UBTS_MidBossmannequinDetect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;

	AttackRangeRadiusSize = 400.0f;
}

void UBTS_MidBossmannequinDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	//AGirlDoll* ControllingGirlDoll = OwnerComp.GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = BlackboardComp->GetValueAsVector("AreaPos");
	//FVector Center = ControllingPawn->GetActorLocation();
	
	FVector DetectRadius = BlackboardComp->GetValueAsVector("AreaSize");
	//float DetectRadius = 600.0f;

	if (nullptr == World) return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeBox(DetectRadius),
		CollisionQueryParam
	);

	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			APlayerableCharacter* PlayerableCharacter = Cast<APlayerableCharacter>(OverlapResult.GetActor());
			AMidBossmannequin* MyMidBossmannequin = Cast<AMidBossmannequin>(ControllingPawn);
			if (PlayerableCharacter && PlayerableCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMidBossmannequinAIController::TargetKey, PlayerableCharacter);
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(AMidBossmannequinAIController::TargetLocationKey, PlayerableCharacter->GetActorLocation());
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMidBossmannequinAIController::IsDieKey, MyMidBossmannequin->isDie);


				return;
			}

		}
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMidBossmannequinAIController::TargetKey, nullptr);

}


