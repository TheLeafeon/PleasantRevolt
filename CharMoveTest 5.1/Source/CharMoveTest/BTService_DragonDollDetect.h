// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "TestMonsterArea.h"
#include "BTService_DragonDollDetect.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBTService_DragonDollDetect : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_DragonDollDetect();

	UPROPERTY(EditAnywhere, Category = "Area")
		ATestMonsterArea* DragonDollArea;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;




};
