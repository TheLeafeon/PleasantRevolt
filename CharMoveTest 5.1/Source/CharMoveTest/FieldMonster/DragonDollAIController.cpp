// Fill out your copyright notice in the Description page of Project Settings.

#include "CharMoveTest/FieldMonster/DragonDollAIController.h"
#include "NavigationSystem.h"
#include "CharMoveTest/FieldMonster/DragonDoll.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ADragonDollAIController::HomePosKey(TEXT("HomePos"));
const FName ADragonDollAIController::TargetKey(TEXT("Target"));
const FName ADragonDollAIController::AreaPosKey(TEXT("AreaPos"));
const FName ADragonDollAIController::AreaSizeKey(TEXT("AreaSize"));

ADragonDollAIController::ADragonDollAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/Monster/AI/BB_DragonDoll.BB_DragonDoll"));
	if (BBObject.Succeeded())
	{
		BBDragonDoll = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Monster/AI/BT_DragonDoll.BT_DragonDoll"));
	if (BTObject.Succeeded())
	{
		BTDragonDoll = BTObject.Object;
	}


}

void ADragonDollAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	/*UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBDragonDoll, BlackboardComp))
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTDragonDoll))
		{

		}
	}*/
	FTimerHandle TimerHandleDragonDoll;

	FTimerDelegate TimerDelegateDragonDoll = FTimerDelegate::CreateUObject(this, &ADragonDollAIController::OnPossessDelayed, InPawn);
	GetWorldTimerManager().SetTimer(TimerHandleDragonDoll, TimerDelegateDragonDoll, 0.2f, false);
}
void ADragonDollAIController::OnPossessDelayed(APawn* InPawn)
{
	if (InPawn == nullptr)
	{
		return;
	}


	MyDragonDoll = Cast<ADragonDoll>(InPawn);

	if (MyDragonDoll == nullptr)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBDragonDoll, BlackboardComp) && MyDragonDoll != nullptr)
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		BlackboardComp->SetValueAsVector(AreaPosKey, MyDragonDoll->MyAreaLocation);
		BlackboardComp->SetValueAsVector(AreaSizeKey, MyDragonDoll->MyAreaSize);

		if (!RunBehaviorTree(BTDragonDoll))
		{

		}
	}
}