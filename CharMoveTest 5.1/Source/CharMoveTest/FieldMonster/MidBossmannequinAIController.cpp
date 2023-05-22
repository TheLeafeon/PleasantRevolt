// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/MidBossmannequinAIController.h"
#include "NavigationSystem.h"
#include "CharMoveTest/FieldMonster/MidBossmannequin.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AMidBossmannequinAIController::HomePosKey(TEXT("HomePos"));
const FName AMidBossmannequinAIController::TargetKey(TEXT("Target"));
const FName AMidBossmannequinAIController::AreaPosKey(TEXT("AreaPos"));
const FName AMidBossmannequinAIController::AreaSizeKey(TEXT("AreaSize"));
const FName AMidBossmannequinAIController::InRangeKey(TEXT("InRange"));
const FName AMidBossmannequinAIController::IsSeeKey(TEXT("IsSee"));
const FName AMidBossmannequinAIController::TargetLocationKey(TEXT("TargetLocation"));
const FName AMidBossmannequinAIController::LastTargetLocationKey(TEXT("LastTargetLocation"));
const FName AMidBossmannequinAIController::RushHitKey(TEXT("RushHit"));
const FName AMidBossmannequinAIController::IsDieKey(TEXT("IsDie"));

AMidBossmannequinAIController::AMidBossmannequinAIController() : BlackboardComp(Blackboard)
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/Monster/AI/BB_MidBossmannequin.BB_MidBossmannequin"));
	if (BBObject.Succeeded())
	{
		BBMidBossmannequin = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Monster/AI/BT_MidBossmannequin.BT_MidBossmannequin"));
	if (BTObject.Succeeded())
	{
		BTMidBossmannequin = BTObject.Object;
	}
}

void AMidBossmannequinAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	FTimerHandle TimerHandleMidBossmannequin;

	FTimerDelegate TimerDelegateMidBossmannequin = FTimerDelegate::CreateUObject(this, &AMidBossmannequinAIController::OnPossessDelayed, InPawn);
	GetWorldTimerManager().SetTimer(TimerHandleMidBossmannequin, TimerDelegateMidBossmannequin, 0.2f, false);
}

void AMidBossmannequinAIController::OnPossessDelayed(APawn* InPawn)
{
	if (InPawn == nullptr)
	{
		return;
	}

	MyMidBossmannequin = Cast<AMidBossmannequin>(InPawn);

	if (MyMidBossmannequin == nullptr)
	{
		return;
	}

	//UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBMidBossmannequin, BlackboardComp) && MyMidBossmannequin != nullptr)
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		BlackboardComp->SetValueAsVector(AreaPosKey, MyMidBossmannequin->MyAreaLocation);
		BlackboardComp->SetValueAsVector(AreaSizeKey, MyMidBossmannequin->MyAreaSize);


		if (!RunBehaviorTree(BTMidBossmannequin))
		{

		}
	}
}

void AMidBossmannequinAIController::PauseBehaviorTree()
{
	SetActorTickEnabled(false); //비헤이비어 트리를 중지
}

void AMidBossmannequinAIController::ResumeBehaviorTree()
{
	SetActorTickEnabled(true); //비헤이비어 트리를 다시 실행
}

FVector AMidBossmannequinAIController::GetLastTargetLocation()
{
	return BlackboardComp->GetValueAsVector(LastTargetLocationKey);
}

void AMidBossmannequinAIController::SetRushStop()
{
	BlackboardComp->SetValueAsBool(RushHitKey, true);
}
