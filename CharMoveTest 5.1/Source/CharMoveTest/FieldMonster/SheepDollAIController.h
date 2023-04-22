// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/SheepDoll.h"
#include "AIController.h"
#include "SheepDollAIController.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API ASheepDollAIController : public AAIController
{
	GENERATED_BODY()
public:
	ASheepDollAIController();

	virtual void OnPossess(APawn* InPawn)override;

	void OnPossessDelayed(APawn* InPawn);

	static const FName HomePosKey;
	static const FName TargetKey;
	static const FName AreaPosKey;
	static const FName AreaSizeKey;
	static const FName TargetLocationKey;
	static const FName SeeKey;
	static const FName TrueKey;
	static const FName StunKey;

	UPROPERTY()
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
		ASheepDoll* MySheepDoll;

	UFUNCTION(BlueprintCallable)
	void SetRushStop();
	UFUNCTION(BlueprintCallable)
	void PlayerAttackHit();
	UFUNCTION(BlueprintCallable)
		void PauseBehaviorTree();
	UFUNCTION(BlueprintCallable)
		void ResumeBehaviorTree();

private:
	UPROPERTY()
		class UBehaviorTree* BTSheepDoll;
	UPROPERTY()
		class UBlackboardData* BBSheepDoll;
	
};
