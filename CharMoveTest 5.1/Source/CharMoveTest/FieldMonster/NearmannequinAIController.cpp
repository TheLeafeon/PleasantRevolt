// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/NearmannequinAIController.h"
#include "NavigationSystem.h"
#include "CharMoveTest/FieldMonster/Nearmannequin.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName ANearmannequinAIController::HomePosKey(TEXT("HomePos"));
const FName ANearmannequinAIController::TargetKey(TEXT("Target"));
const FName ANearmannequinAIController::AreaPosKey(TEXT("AreaPos"));
const FName ANearmannequinAIController::AreaSizeKey(TEXT("AreaSize"));
const FName ANearmannequinAIController::IsDieKey(TEXT("IsDie"));

ANearmannequinAIController::ANearmannequinAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/Monster/AI/BB_Nearmannequin.BB_Nearmannequin"));
	if (BBObject.Succeeded())
	{
		BBNearmannequin = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Monster/AI/BT_Nearmannequin.BT_Nearmannequin"));
	if (BTObject.Succeeded())
	{
		BTNearmannequin = BTObject.Object;
	}
}

void ANearmannequinAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	FTimerHandle TimerHandleNearmannequin;

	FTimerDelegate TimerDelegateNearmannequin = FTimerDelegate::CreateUObject(this, &ANearmannequinAIController::OnPossessDelayed, InPawn);
	GetWorldTimerManager().SetTimer(TimerHandleNearmannequin, TimerDelegateNearmannequin, 0.2f, false);
}

void ANearmannequinAIController::OnPossessDelayed(APawn* InPawn)
{
	if (InPawn == nullptr)
	{
		return;
	}

	MyNearmannequin = Cast<ANearmannequin>(InPawn);

	if (MyNearmannequin == nullptr)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBNearmannequin, BlackboardComp) && MyNearmannequin != nullptr)
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		BlackboardComp->SetValueAsVector(AreaPosKey, MyNearmannequin->MyAreaLocation);
		BlackboardComp->SetValueAsVector(AreaSizeKey, MyNearmannequin->MyAreaSize);

		if (!RunBehaviorTree(BTNearmannequin))
		{

		}
	}

}

void ANearmannequinAIController::PauseBehaviorTree()
{
	SetActorTickEnabled(false); //비헤이비어 트리를 중지
}

void ANearmannequinAIController::ResumeBehaviorTree()
{
	SetActorTickEnabled(true); //비헤이비어 트리를 다시 실행
}
