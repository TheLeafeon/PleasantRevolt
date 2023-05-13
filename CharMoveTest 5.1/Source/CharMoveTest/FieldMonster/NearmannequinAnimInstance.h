// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NearmannequinAnimInstance.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UNearmannequinAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UNearmannequinAnimInstance();

	void PlayAttack_MeleeMontage();

	FOnAttackHitCheckDelegate OnAttackHitCheck;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack_Melee", Meta = (AllowPrivateAccess = true))
	UAnimMontage* Attack_MeleeMontage;

	UFUNCTION()
	void AnimNotify_AttackHitCheck();
};
