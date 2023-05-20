// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PlasticDoll_AIController.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API APlasticDoll_AIController : public AAIController
{
	GENERATED_BODY()
	
private:
	APlasticDoll_AIController();

	//virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
	class UBehaviorTree* BTAsset;
	UPROPERTY()
	class UBlackboardData* BBAsset;
	UPROPERTY()
	UBlackboardComponent* BlackboardComp;

public:
	UFUNCTION(BlueprintCallable)
	void SetBehaviorTree();
};
