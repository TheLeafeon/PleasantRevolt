// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/GirlDollAIController.h"
#include "NavigationSystem.h"
#include "CharMoveTest/FieldMonster/GirlDoll.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AGirlDollAIController::HomePosKey(TEXT("HomePos"));
const FName AGirlDollAIController::TargetKey(TEXT("Target"));
const FName AGirlDollAIController::AreaPosKey(TEXT("AreaPos"));
const FName AGirlDollAIController::AreaSizeKey(TEXT("AreaSize"));


AGirlDollAIController::AGirlDollAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/Monster/AI/BB_GirlDoll.BB_GirlDoll"));
	if (BBObject.Succeeded())
	{
		BBGirlDoll = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Monster/AI/BT_GirlDoll.BT_GirlDoll"));
	if (BTObject.Succeeded())
	{
		BTGirlDoll = BTObject.Object;
	}
}

void AGirlDollAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	FTimerHandle TimerHandleGirlDoll;

	FTimerDelegate TimerDelegateGirlDoll = FTimerDelegate::CreateUObject(this, &AGirlDollAIController::OnPossessDelayed, InPawn);
	GetWorldTimerManager().SetTimer(TimerHandleGirlDoll, TimerDelegateGirlDoll, 0.2f, false);

}

void AGirlDollAIController::OnPossessDelayed(APawn* InPawn)
{
	if (InPawn == nullptr)
	{
		return;
	}


	MyGirlDoll = Cast<AGirlDoll>(InPawn);

	if (MyGirlDoll == nullptr)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBGirlDoll, BlackboardComp) && MyGirlDoll != nullptr)
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		BlackboardComp->SetValueAsVector(AreaPosKey, MyGirlDoll->MyAreaLocation);
		BlackboardComp->SetValueAsVector(AreaSizeKey, MyGirlDoll->MyAreaSize);



		if (!RunBehaviorTree(BTGirlDoll))
		{

		}
	}
}

