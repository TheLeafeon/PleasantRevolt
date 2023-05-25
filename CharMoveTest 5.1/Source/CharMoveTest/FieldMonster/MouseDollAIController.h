// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/MouseDoll.h"
#include "AIController.h"
#include "MouseDollAIController.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API AMouseDollAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMouseDollAIController();
	
	virtual void OnPossess(APawn* InPawn)override;

	void OnPossessDelayed(APawn* InPawn);

	UFUNCTION(BlueprintCallable)
		void PauseBehaviorTree();
	UFUNCTION(BlueprintCallable)
		void ResumeBehaviorTree();

	static const FName HomePosKey;
	static const FName TargetKey;
	static const FName AreaPosKey;
	static const FName AreaSizeKey;
	static const FName IsDieKey;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
		AMouseDoll *MyMouseDoll;
private:
	UPROPERTY()
		class UBehaviorTree* BTMouseDoll;
	UPROPERTY()
		class UBlackboardData* BBMouseDoll;
};
