// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DoveDollAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UDoveDollAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UDoveDollAnimInstance();

	void PlayAttackMontage();
	void PlayHitMontage();
	void PlayDeathMontage();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit", Meta = (AllowPrivateAccess = true))
		UAnimMontage* HitMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Death", Meta = (AllowPrivateAccess = true))
		UAnimMontage* DeathMontage;
	
};
