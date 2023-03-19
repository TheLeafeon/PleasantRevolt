// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveTo_GirlDollIsSearch.generated.h"


/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UBTTask_MoveTo_GirlDollIsSearch : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
public:
	UBTTask_MoveTo_GirlDollIsSearch();

	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

//private:
	//void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

	
};
