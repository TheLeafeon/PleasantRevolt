// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTService_MouseDollDetect.h"
#include "CharMoveTest/FieldMonster/MouseDollAIController.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_MouseDollDetect::UBTService_MouseDollDetect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_MouseDollDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
			if (PlayerableCharacter && PlayerableCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMouseDollAIController::TargetKey, PlayerableCharacter);

				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMouseDollAIController::TargetKey, nullptr);

}
