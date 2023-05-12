// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTS_NearmannequinDetect.h"
#include "CharMoveTest/FieldMonster/NearmannequinAIController.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTS_NearmannequinDetect::UBTS_NearmannequinDetect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTS_NearmannequinDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
			if (PlayerableCharacter && PlayerableCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ANearmannequinAIController::TargetKey, PlayerableCharacter);


				//DrawDebugPoint(World, PlayerableCharacter->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				//DrawDebugLine(World, ControllingPawn->GetActorLocation(), PlayerableCharacter->GetActorLocation(), FColor::Blue, false, 0.27f);
				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(ANearmannequinAIController::TargetKey, nullptr);
}
