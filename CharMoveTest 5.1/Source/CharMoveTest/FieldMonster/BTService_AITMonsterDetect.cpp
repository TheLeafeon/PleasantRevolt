// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTService_AITMonsterDetect.h"
#include "CharMoveTest/FieldMonster/AITMonsterAIController.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_AITMonsterDetect::UBTService_AITMonsterDetect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_AITMonsterDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();

	float DetectRadius = 600.0f;

	if (nullptr == World) return;
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

	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			APlayerableCharacter* PlayerableCharacter = Cast<APlayerableCharacter>(OverlapResult.GetActor());
			if (PlayerableCharacter && PlayerableCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AAITMonsterAIController::TargetKey, PlayerableCharacter);
				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(AAITMonsterAIController::TargetKey, nullptr);
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);

}
