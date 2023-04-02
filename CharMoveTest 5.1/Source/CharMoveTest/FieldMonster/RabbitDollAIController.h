// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/RabbitDoll.h"
#include "AIController.h"
#include "RabbitDollAIController.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API ARabbitDollAIController : public AAIController
{
	GENERATED_BODY()
public:

	ARabbitDollAIController();

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable)
	void OnPossessDelayed(APawn* InPawn);

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
	static const FName AreaPosKey;
	static const FName AreaSizeKey;

	UPROPERTY(BlueprintReadOnly, Category = "AI")
		ARabbitDoll* MyRabbitDoll;

private:
	UPROPERTY()
		class UBehaviorTree* BTRabbitDoll;
	UPROPERTY()
		class UBlackboardData* BBRabbitDoll;
	
};
