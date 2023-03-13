// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CharMoveTest/Boss/BossAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CharMoveTest/Boss/Boss_BlackBoardKey.h"
#include "FindPlayer_BTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UFindPlayer_BTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	UFindPlayer_BTTaskNode();

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	//float moveSpeed;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
