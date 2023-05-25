// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/Nearmannequin.h"
#include "AIController.h"
#include "NearmannequinAIController.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API ANearmannequinAIController : public AAIController
{
	GENERATED_BODY()
public:
	ANearmannequinAIController();

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
		ANearmannequin* MyNearmannequin;
private:
	UPROPERTY()
		class UBehaviorTree* BTNearmannequin;
	UPROPERTY()
		class UBlackboardData* BBNearmannequin;
	
};
