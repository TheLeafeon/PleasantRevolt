// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CharMoveTest/Boss/PD_Body_Character.h"
#include "PD_3Phase_Collapse_BTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UPD_3Phase_Collapse_BTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
	
private:
	UPD_3Phase_Collapse_BTTaskNode();

	APD_Body_Character* Body;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
