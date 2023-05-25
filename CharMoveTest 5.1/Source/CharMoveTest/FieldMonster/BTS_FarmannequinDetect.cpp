// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/BTS_FarmannequinDetect.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "CharMoveTest/FieldMonster/FarmannequinAIController.h"
#include "CharMoveTest/FieldMonster/Farmannequin.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTS_FarmannequinDetect::UBTS_FarmannequinDetect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTS_FarmannequinDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = BlackboardComp->GetValueAsVector("AreaPos");

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
			AFarmannequin* MyFarmannequin = Cast<AFarmannequin>(ControllingPawn);
			if (PlayerableCharacter && PlayerableCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AFarmannequinAIController::TargetKey, PlayerableCharacter);
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(AFarmannequinAIController::IsDieKey, MyFarmannequin->isDie);

				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(AFarmannequinAIController::TargetKey, nullptr);

}
