// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/DoveDollAIController.h"
#include "NavigationSystem.h"
#include "CharMoveTest/FieldMonster/DoveDoll.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ADoveDollAIController::HomePosKey(TEXT("HomePos"));
const FName ADoveDollAIController::TargetKey(TEXT("Target"));
const FName ADoveDollAIController::AreaPosKey(TEXT("AreaPos"));
const FName ADoveDollAIController::AreaSizeKey(TEXT("AreaSize"));

ADoveDollAIController::ADoveDollAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/Monster/AI/BB_DoveDoll.BB_DoveDoll"));
	if (BBObject.Succeeded())
	{
		BBDoveDoll = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Monster/AI/BT_DoveDoll.BT_DoveDoll"));
	if (BTObject.Succeeded())
	{
		BTDoveDoll = BTObject.Object;
	}
}

void ADoveDollAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	FTimerHandle TimerHandleDoveDoll;

	FTimerDelegate TimerDelegateDoveDoll = FTimerDelegate::CreateUObject(this, &ADoveDollAIController::OnPossessDelayed, InPawn);
	GetWorldTimerManager().SetTimer(TimerHandleDoveDoll, TimerDelegateDoveDoll, 0.2f, false);
}

void ADoveDollAIController::OnPossessDelayed(APawn* InPawn)
{
	if (InPawn == nullptr)
	{
		return;
	}


	MyDoveDoll = Cast<ADoveDoll>(InPawn);

	if (MyDoveDoll == nullptr)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBDoveDoll, BlackboardComp) && MyDoveDoll != nullptr)
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		BlackboardComp->SetValueAsVector(AreaPosKey, MyDoveDoll->MyAreaLocation);
		BlackboardComp->SetValueAsVector(AreaSizeKey, MyDoveDoll->MyAreaSize);

		if (!RunBehaviorTree(BTDoveDoll))
		{

		}
	}
}
