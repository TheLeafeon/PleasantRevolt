// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PD_SmashWait_BTTaskNode.h"
#include "Kismet/GameplayStatics.h"

UPD_SmashWait_BTTaskNode::UPD_SmashWait_BTTaskNode()
{
	NodeName = TEXT("SmashWait");

	static ConstructorHelpers::FObjectFinder<UBlueprint> BPD_FallDecal(TEXT("/Game/Boss/2Stage/PD_FallDecal.PD_FallDecal"));
	if (BPD_FallDecal.Object)
	{
		PD_FallDecal = (UClass*)BPD_FallDecal.Object->GeneratedClass;
	}
}

EBTNodeResult::Type UPD_SmashWait_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm) == nullptr && OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm) == nullptr)
	{
		//3페로 넘어가기
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey2::isArmLive, false);

		return EBTNodeResult::Succeeded;
	}
	else if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm) == nullptr)
	{
		RandomValue = 0.6;
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey2::isLeftArm, false);
	}
	else if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm) == nullptr)
	{
		RandomValue = 0.1;
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(bossKey2::isLeftArm, true);
	}
	else
	{
		RandomValue = FMath::RandRange(0.0f, 1.0f);
	}

	//다음 테스크를 위해 랜덤값 저장
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(bossKey2::randomArm, RandomValue);

	//빨간원 생성하기
	FRotator Rotator;
	FVector SpawnLocation = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();

	APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PD_FallDecal, SpawnLocation, Rotator);

	if (RandomValue <= 0.5 && OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm) != nullptr)
	{
		LArm = Cast<APD_LeftArm>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm));
		LArm->SmashWait();
		LArm->SetFallDecalPawn(SpawnedPawn);
	}
	else if (RandomValue > 0.5 && OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm) != nullptr)
	{
		RArm = Cast<APD_RightArm>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm));
		RArm->SmashWait();
		RArm->SetFallDecalPawn(SpawnedPawn);
	}
	
	return EBTNodeResult::Succeeded;
}