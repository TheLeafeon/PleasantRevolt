// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/MidBossmannequin.h"
#include "AIController.h"
#include "MidBossmannequinAIController.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API AMidBossmannequinAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMidBossmannequinAIController();

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
	static const FName InRangeKey;
	static const FName IsSeeKey;
	static const FName TargetLocationKey;
	static const FName LastTargetLocationKey;
	static const FName RushHitKey;
	static const FName IsDieKey;

	UPROPERTY()
		UBlackboardComponent* BlackboardComp;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
		AMidBossmannequin* MyMidBossmannequin;

	UFUNCTION(BlueprintCallable)
	FVector GetLastTargetLocation();

	UFUNCTION(BlueprintCallable)
	void SetRushStop();
	
private:
	UPROPERTY()
		class UBehaviorTree* BTMidBossmannequin;
	UPROPERTY()
		class UBlackboardData* BBMidBossmannequin;
	
};
