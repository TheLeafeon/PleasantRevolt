// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CharMoveTest/Boss/BossAIController.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "CharMoveTest/Boss/Boss_BlackBoardKey.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Detect2_BTService.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UDetect2_BTService : public UBTService
{
	GENERATED_BODY()

private:
	UDetect2_BTService();

	UPROPERTY()
	float DetectRadius; //범위 반지름

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
