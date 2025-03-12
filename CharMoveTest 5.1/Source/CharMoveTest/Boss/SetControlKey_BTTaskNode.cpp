// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/SetControlKey_BTTaskNode.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

USetControlKey_BTTaskNode::USetControlKey_BTTaskNode()
{
	NodeName = TEXT("Set Key");

	// 블루프린트 클래스 찾기 (생성자에서만 됨)
	static ConstructorHelpers::FClassFinder<AActor> BearDollInfoBPClass(TEXT("/Game/Boss/1Stage/BearDollInfo"));
	if (BearDollInfoBPClass.Class != NULL)
	{
		UClass* BearDollInfoClass = BearDollInfoBPClass.Class;

		// 액터 찾기
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), BearDollInfoClass, FoundActors);

		for (AActor* Actor : FoundActors)
		{
			if (Actor != nullptr)
			{
				BearDollInfo = Actor;
			}
		}
	}
}

EBTNodeResult::Type USetControlKey_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn != nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(bossKey::enemyActor, PlayerPawn);
	}

	if (BearDollInfo != nullptr)
	{
		FName FunctionName = "GetDetectRadius"; // 블루프린트 함수 이름
		UFunction* Function = BearDollInfo->FindFunction(FunctionName);

		if (Function != nullptr)
		{
			struct FDynamicArgs
			{
				float Return;
			};
			FDynamicArgs Args;
			Args.Return = -1.f;

			BearDollInfo->ProcessEvent(Function, &Args);
			UE_LOG(LogTemp, Warning, TEXT("%f"), Args.Return);
			OwnerComp.GetBlackboardComponent()->SetValueAsFloat(bossKey::detectRadius, Args.Return);
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::setting, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::keyTrue, true);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::inRange, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey::isRotate, false);

	return EBTNodeResult::Succeeded;
}
