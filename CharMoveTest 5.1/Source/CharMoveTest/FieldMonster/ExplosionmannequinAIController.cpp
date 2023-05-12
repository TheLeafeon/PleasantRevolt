// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/ExplosionmannequinAIController.h"
#include "NavigationSystem.h"
#include "CharMoveTest/FieldMonster/Explosionmannequin.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AExplosionmannequinAIController::HomePosKey(TEXT("HomePos"));
const FName AExplosionmannequinAIController::TargetKey(TEXT("Target"));
const FName AExplosionmannequinAIController::AreaPosKey(TEXT("AreaPos"));
const FName AExplosionmannequinAIController::AreaSizeKey(TEXT("AreaSize"));
const FName AExplosionmannequinAIController::isDieKey(TEXT("isDie"));

AExplosionmannequinAIController::AExplosionmannequinAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/Monster/AI/BB_Explosionmannequin.BB_Explosionmannequin"));
	if (BBObject.Succeeded())
	{
		BBExplosionmannequin = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/Monster/AI/BT_Explosionmannequin.BT_Explosionmannequin"));
	if (BTObject.Succeeded())
	{
		BTExplosionmannequin = BTObject.Object;
	}
}

void AExplosionmannequinAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	FTimerHandle TimerHandleExplosionmannequin;

	FTimerDelegate TimerDelegateExplosionmannequin = FTimerDelegate::CreateUObject(this, &AExplosionmannequinAIController::OnPossessDelayed, InPawn);
	GetWorldTimerManager().SetTimer(TimerHandleExplosionmannequin, TimerDelegateExplosionmannequin, 0.2f, false);
}

void AExplosionmannequinAIController::OnPossessDelayed(APawn* InPawn)
{
	if (InPawn == nullptr)
	{
		return;
	}

	MyExplosionmannequin = Cast<AExplosionmannequin>(InPawn);

	if (MyExplosionmannequin == nullptr)
	{
		return;
	}

	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	if (UseBlackboard(BBExplosionmannequin, BlackboardComp) && MyExplosionmannequin != nullptr)
	{
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		BlackboardComp->SetValueAsVector(AreaPosKey, MyExplosionmannequin->MyAreaLocation);
		BlackboardComp->SetValueAsVector(AreaSizeKey, MyExplosionmannequin->MyAreaSize);

		if (!RunBehaviorTree(BTExplosionmannequin))
		{

		}
	}
}


void AExplosionmannequinAIController::PauseBehaviorTree()
{
	SetActorTickEnabled(false); //비헤이비어 트리를 중지
}

void AExplosionmannequinAIController::ResumeBehaviorTree()
{
	SetActorTickEnabled(true); //비헤이비어 트리를 다시 실행
}

void AExplosionmannequinAIController::ControllingPawnisDie()
{
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	BlackboardComp->SetValueAsBool(isDieKey, true);
}
