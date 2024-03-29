// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PD_SmashWait_BTTaskNode.h"
#include "Kismet/GameplayStatics.h"

UPD_SmashWait_BTTaskNode::UPD_SmashWait_BTTaskNode()
{
	NodeName = TEXT("SmashWait");
}

EBTNodeResult::Type UPD_SmashWait_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!PD_FallDecal)
	{
		return EBTNodeResult::Failed;
	}

	//팔 상태 확인
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
	//다음 테스크를 위해 위의 랜덤값 저장
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(bossKey2::randomArm, RandomValue);

	//플레이어 추격 Obj 생성하기
	FVector SpawnLocation = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
	APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(PD_FallDecal, SpawnLocation, FRotator(0.0f, 90.0f, 0.0f));

	//랜덤값에 따라 LeftArm, RightArm 둘 중 하나만 움직이도록 함
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