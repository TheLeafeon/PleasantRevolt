// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/RabbitDollAIController.h"
#include "NavigationSystem.h"
#include "CharMoveTest/FieldMonster/RabbitDoll.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ARabbitDollAIController::HomePosKey(TEXT("HomePos"));
const FName ARabbitDollAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName ARabbitDollAIController::TargetKey(TEXT("Target"));
const FName ARabbitDollAIController::AreaPosKey(TEXT("AreaPos"));
const FName ARabbitDollAIController::AreaSizeKey(TEXT("AreaSize"));


ARabbitDollAIController::ARabbitDollAIController()
{

	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/Monster/AI/BB_RabbitDoll.BB_RabbitDoll"));
	if (BBObject.Succeeded())
	{
		BBRabbitDoll = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Monster/AI/BT_RabbitDoll.BT_RabbitDoll"));
	if (BTObject.Succeeded())
	{
		BTRabbitDoll = BTObject.Object;
	}
}

void ARabbitDollAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	FTimerHandle TimerHandleRabbitDoll;

	FTimerDelegate TimerDelegateRabbitDoll = FTimerDelegate::CreateUObject(this, &ARabbitDollAIController::OnPossessDelayed, InPawn);
	GetWorldTimerManager().SetTimer(TimerHandleRabbitDoll, TimerDelegateRabbitDoll, 0.5f, false);

}

void ARabbitDollAIController::OnPossessDelayed(APawn* InPawn)
{
	if (InPawn == nullptr)
	{
		return;
	}


	MyRabbitDoll = Cast<ARabbitDoll>(InPawn);

	if (MyRabbitDoll == nullptr)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBRabbitDoll, BlackboardComp) && MyRabbitDoll != nullptr)
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		BlackboardComp->SetValueAsVector(AreaPosKey, MyRabbitDoll->MyAreaLocation);
		BlackboardComp->SetValueAsVector(AreaSizeKey, MyRabbitDoll->MyAreaSize);

		


		
		if (!RunBehaviorTree(BTRabbitDoll))
		{

		}
	}
}

