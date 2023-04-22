// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/SheepDollAIController.h"
#include "NavigationSystem.h"
#include "CharMoveTest/FieldMonster/SheepDoll.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ASheepDollAIController::HomePosKey(TEXT("HomePos"));
const FName ASheepDollAIController::TargetKey(TEXT("Target"));
const FName ASheepDollAIController::AreaPosKey(TEXT("AreaPos"));
const FName ASheepDollAIController::AreaSizeKey(TEXT("AreaSize"));
const FName ASheepDollAIController::TargetLocationKey(TEXT("TargetLocation"));
const FName ASheepDollAIController::SeeKey(TEXT("See"));
const FName ASheepDollAIController::TrueKey(TEXT("True"));
const FName ASheepDollAIController::StunKey(TEXT("Stun"));

ASheepDollAIController::ASheepDollAIController() : BlackboardComp(Blackboard)
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/Monster/AI/BB_SheepDoll.BB_SheepDoll"));
	if (BBObject.Succeeded())
	{
		BBSheepDoll = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Monster/AI/BT_SheepDoll.BT_SheepDoll"));
	if (BTObject.Succeeded())
	{
		BTSheepDoll = BTObject.Object;
	}
}

void ASheepDollAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	FTimerHandle TimerHandleMouseDoll;

	FTimerDelegate TimerDelegateMouseDoll = FTimerDelegate::CreateUObject(this, &ASheepDollAIController::OnPossessDelayed, InPawn);
	GetWorldTimerManager().SetTimer(TimerHandleMouseDoll, TimerDelegateMouseDoll, 0.2f, false);
}

void ASheepDollAIController::OnPossessDelayed(APawn* InPawn)
{
	if (InPawn == nullptr)
	{
		return;
	}

	MySheepDoll = Cast<ASheepDoll>(InPawn);

	if (MySheepDoll == nullptr)
	{
		return;
	}

	//UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBSheepDoll, BlackboardComp) && MySheepDoll != nullptr)
	{
		
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		BlackboardComp->SetValueAsVector(AreaPosKey, MySheepDoll->MyAreaLocation);
		BlackboardComp->SetValueAsVector(AreaSizeKey, MySheepDoll->MyAreaSize);
		BlackboardComp->SetValueAsBool(SeeKey, false);
		BlackboardComp->SetValueAsBool(TrueKey, true);
		BlackboardComp->SetValueAsBool(StunKey, false);

		if (!RunBehaviorTree(BTSheepDoll))
		{

		}
	}
}

void ASheepDollAIController::SetRushStop()
{
	BlackboardComp->SetValueAsBool(StunKey, true);
}

void ASheepDollAIController::PlayerAttackHit()
{
	BlackboardComp->SetValueAsBool(StunKey, false);
	BlackboardComp->SetValueAsBool(SeeKey, false);
}

void ASheepDollAIController::PauseBehaviorTree()
{
	SetActorTickEnabled(false); //비헤이비어 트리를 중지
}

void ASheepDollAIController::ResumeBehaviorTree()
{
	SetActorTickEnabled(true); //비헤이비어 트리를 다시 실행
}
