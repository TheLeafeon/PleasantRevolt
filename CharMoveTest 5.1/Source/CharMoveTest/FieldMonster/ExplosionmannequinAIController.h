// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/Explosionmannequin.h"
#include "AIController.h"
#include "ExplosionmannequinAIController.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API AExplosionmannequinAIController : public AAIController
{
	GENERATED_BODY()
public:
	AExplosionmannequinAIController();

	virtual void OnPossess(APawn* InPawn)override;

	void OnPossessDelayed(APawn* InPawn);

	UFUNCTION(BlueprintCallable)
		void PauseBehaviorTree();
	UFUNCTION(BlueprintCallable)
		void ResumeBehaviorTree();
	UFUNCTION(BlueprintCallable)
		void ControllingPawnisDie();

	static const FName HomePosKey;
	static const FName TargetKey;
	static const FName AreaPosKey;
	static const FName AreaSizeKey;
	static const FName isDieKey;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
		AExplosionmannequin* MyExplosionmannequin;
private:
	UPROPERTY()
		class UBehaviorTree* BTExplosionmannequin;
	UPROPERTY()
		class UBlackboardData* BBExplosionmannequin;

	
};
