// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CharMoveTest/Boss/Boss_BlackBoardKey.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CharMoveTest/Boss/PD_RightArm.h"
#include "CharMoveTest/Boss/PD_LeftArm.h"
#include "Kismet/GameplayStatics.h"
#include "PD_SmashWait_BTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UPD_SmashWait_BTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	UPD_SmashWait_BTTaskNode();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	float RandomValue; //이 값에 따라 어떤 팔이 명령을 받는지 결정됨
	APD_LeftArm* LArm;
	APD_RightArm* RArm;
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class APawn> PD_FallDecal; //플레이어 추격 오브제
};
