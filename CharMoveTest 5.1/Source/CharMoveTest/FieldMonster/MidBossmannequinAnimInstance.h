// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MidBossmannequinAnimInstance.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnInRangeAttackHitCheckDelegate);

UCLASS()
class CHARMOVETEST_API UMidBossmannequinAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMidBossmannequinAnimInstance();

	void PlayInRangeAttackMontage();

	FOnInRangeAttackHitCheckDelegate OnInRangeAttackHitCheck;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InRangeAttack", Meta = (AllowPrivateAccess = true))
	UAnimMontage* InRangeAttackMontage;

	UFUNCTION()
	void AnimNotify_InRangeAttackHitCheck();
	
};
