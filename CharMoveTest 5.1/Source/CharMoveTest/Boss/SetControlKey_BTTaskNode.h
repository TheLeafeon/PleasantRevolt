// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CharMoveTest/Boss/Boss_BlackBoardKey.h"
//#include "CharMoveTest/Boss/BossAI_NumericalControl.h"
#include "CharMoveTest/Boss/BossAI_GameInstanceSubsystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SetControlKey_BTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API USetControlKey_BTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

private:
	USetControlKey_BTTaskNode();

	//ABossAI_NumericalControl* Numericalcontrol;
	UPROPERTY()
	UBossAI_GameInstanceSubsystem* BossAIGISS;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
