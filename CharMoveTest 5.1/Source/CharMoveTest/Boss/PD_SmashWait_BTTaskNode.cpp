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
	if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm) == nullptr)
	{
		RandomValue = 0.6;
	}
	else if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm) == nullptr)
	{
		RandomValue = 0.1;
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
	
	//만약 어느 한 쪽이 박살났으면 한 쪽으로 고정 시켜줘야함

	if (RandomValue <= 0.5)
	{
		LArm = Cast<APD_LeftArm>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::leftArm));
		LArm->SmashWait();
		LArm->SetFallDecalPawn(SpawnedPawn);
	}
	else
	{
		RArm = Cast<APD_RightArm>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(bossKey2::rightArm));
		RArm->SmashWait();
		RArm->SetFallDecalPawn(SpawnedPawn);
	}
	
	return EBTNodeResult::Succeeded;
}