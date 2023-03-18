// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CharMoveTest/Boss/Boss_BlackBoardKey.h"
#include "BossAIController.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API ABossAIController : public AAIController
{
	GENERATED_BODY()

private:
	ABossAIController();

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
	class UBehaviorTree* BTAsset;
	UPROPERTY()
	class UBlackboardData* BBAsset;
	UPROPERTY()
	UBlackboardComponent* BlackboardComp;

public:
	UFUNCTION(BlueprintCallable)
	void PauseBehaviorTree();
	UFUNCTION(BlueprintCallable)
	void ResumeBehaviorTree();
	UFUNCTION(BlueprintCallable)
	void SetEnemy(AActor* enemy);
	UFUNCTION(BlueprintCallable)
	void SetStop(bool stop);
};
