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
	void PlayRollingMontage();
	void PlayBeHitMontage();
	void PlayDeathMontage();

private :
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Rolling, Meta = (AllowPrivateAccess = true))
		UAnimMontage* Rolling_AnimMontage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* BeHit_AnimMontage;

public :
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* NearWeapon1_AnimMontage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* NearWeapon2_AnimMontage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* Death_AnimMontage;
};
