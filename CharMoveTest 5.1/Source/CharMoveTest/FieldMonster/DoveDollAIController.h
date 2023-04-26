// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/DoveDoll.h"
#include "AIController.h"
#include "DoveDollAIController.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API ADoveDollAIController : public AAIController
{
	GENERATED_BODY()
public:
	ADoveDollAIController();
	virtual void OnPossess(APawn* InPawn) override;

	void OnPossessDelayed(APawn* InPawn);

	static const FName HomePosKey;
	static const FName TargetKey;
	static const FName AreaPosKey;
	static const FName AreaSizeKey;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
	ADoveDoll* MyDoveDoll;


private:
	UPROPERTY()
		class UBehaviorTree* BTDoveDoll;
	UPROPERTY()
		class UBlackboardData* BBDoveDoll;

	
};
