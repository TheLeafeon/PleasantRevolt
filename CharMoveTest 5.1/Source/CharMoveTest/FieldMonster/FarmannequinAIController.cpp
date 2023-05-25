// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/FarmannequinAIController.h"
#include "CharMoveTest/FieldMonster/Farmannequin.h"
#include "NavigationSystem.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AFarmannequinAIController::HomePosKey(TEXT("HomePos"));
const FName AFarmannequinAIController::TargetKey(TEXT("Target"));
const FName AFarmannequinAIController::AreaPosKey(TEXT("AreaPos"));
const FName AFarmannequinAIController::AreaSizeKey(TEXT("AreaSize"));
const FName AFarmannequinAIController::IsDieKey(TEXT("IsDie"));

AFarmannequinAIController::AFarmannequinAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/Monster/AI/BB_Farmannequin.BB_Farmannequin"));
	if (BBObject.Succeeded())
	{
		BBFarmannequin = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Monster/AI/BT_Farmannequin.BT_Farmannequin"));
	if (BTObject.Succeeded())
	{
		BTFarmannequin = BTObject.Object;
	}
}

void AFarmannequinAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	FTimerHandle TimerHandleFarmannequin;

	FTimerDelegate TimerDelegateFarmannequin = FTimerDelegate::CreateUObject(this, &AFarmannequinAIController::OnPossessDelayed, InPawn);
	GetWorldTimerManager().SetTimer(TimerHandleFarmannequin, TimerDelegateFarmannequin, 0.2f, false);

}

void AFarmannequinAIController::OnPossessDelayed(APawn* InPawn)
{
	if (InPawn == nullptr)
	{
		return;
	}


	MyFarmannequin = Cast<AFarmannequin>(InPawn);

	if (MyFarmannequin == nullptr)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBFarmannequin, BlackboardComp) && MyFarmannequin != nullptr)
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		BlackboardComp->SetValueAsVector(AreaPosKey, MyFarmannequin->MyAreaLocation);
		BlackboardComp->SetValueAsVector(AreaSizeKey, MyFarmannequin->MyAreaSize);

		if (!RunBehaviorTree(BTFarmannequin))
		{

		}
	}
}
