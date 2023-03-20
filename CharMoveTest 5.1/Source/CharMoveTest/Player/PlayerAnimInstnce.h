// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstnce.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UPlayerAnimInstnce : public UAnimInstance
{
	GENERATED_BODY()

	UPlayerAnimInstnce();

public:
	void PlaySampleMontage();
	void PlayMeleeAttackMontage();
	void PlayBeHitMontage();
	void PlayDeathMontage();

private :
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Sample", Meta = (AllowPrivateAccess = true))
		UAnimMontage* Sample;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* BeHit_AnimMontage;

public :
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* Attack_AnimMontage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* Death_AnimMontage;
};
