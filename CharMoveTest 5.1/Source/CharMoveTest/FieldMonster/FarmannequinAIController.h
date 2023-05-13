// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CharMoveTest/FieldMonster/Farmannequin.h"
#include "FarmannequinAIController.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API AFarmannequinAIController : public AAIController
{
	GENERATED_BODY()
public:
	AFarmannequinAIController();

	virtual void OnPossess(APawn* InPawn) override;

	void OnPossessDelayed(APawn* InPawn);

	static const FName HomePosKey;
	static const FName TargetKey;
	static const FName AreaPosKey;
	static const FName AreaSizeKey;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
	AFarmannequin* MyFarmannequin;

private:
	UPROPERTY()
		class UBehaviorTree* BTFarmannequin;
	UPROPERTY()
		class UBlackboardData* BBFarmannequin;
	
};
