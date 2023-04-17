// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/MouseDollAIController.h"
#include "NavigationSystem.h"
#include "CharMoveTest/FieldMonster/MouseDoll.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AMouseDollAIController::HomePosKey(TEXT("HomePos"));
const FName AMouseDollAIController::TargetKey(TEXT("Target"));
const FName AMouseDollAIController::AreaPosKey(TEXT("AreaPos"));
const FName AMouseDollAIController::AreaSizeKey(TEXT("AreaSize"));

AMouseDollAIController::AMouseDollAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/Monster/AI/BB_MouseDoll.BB_MouseDoll"));
	if (BBObject.Succeeded())
	{
		BBMouseDoll = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Monster/AI/BT_MouseDoll.BT_MouseDoll"));
	if (BTObject.Succeeded())
	{
		BTMouseDoll = BTObject.Object;
	}
}

void AMouseDollAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	FTimerHandle TimerHandleMouseDoll;

	FTimerDelegate TimerDelegateMouseDoll = FTimerDelegate::CreateUObject(this, &AMouseDollAIController::OnPossessDelayed, InPawn);
	GetWorldTimerManager().SetTimer(TimerHandleMouseDoll, TimerDelegateMouseDoll, 0.2f, false);
}

void AMouseDollAIController::OnPossessDelayed(APawn* InPawn)
{
	if (InPawn == nullptr)
	{
		return;
	}

	MyMouseDoll = Cast<AMouseDoll>(InPawn);

	if (MyMouseDoll == nullptr)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBMouseDoll, BlackboardComp) && MyMouseDoll != nullptr)
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		BlackboardComp->SetValueAsVector(AreaPosKey, MyMouseDoll->MyAreaLocation);
		BlackboardComp->SetValueAsVector(AreaSizeKey, MyMouseDoll->MyAreaSize);

		if (!RunBehaviorTree(BTMouseDoll))
		{

		}
	}
}
