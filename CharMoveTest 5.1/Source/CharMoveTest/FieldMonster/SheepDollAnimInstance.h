// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SheepDollAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API USheepDollAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	USheepDollAnimInstance();

	void PlayRush_ReadyMontage();
	void PlayRushMontage();
	void PlayHitMontage();
	void PlayDeathMontage();
	void PlayStunMontage();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rush_Ready", Meta = (AllowPrivateAccess = true))
		UAnimMontage* Rush_ReadyMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rush", Meta = (AllowPrivateAccess = true))
		UAnimMontage* RushMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit", Meta = (AllowPrivateAccess = true))
		UAnimMontage* HitMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Death", Meta = (AllowPrivateAccess = true))
		UAnimMontage* DeathMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stun", Meta = (AllowPrivateAccess = true))
		UAnimMontage* StunMontage;
	
};
