// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MouseDollAnimInstance.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UMouseDollAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMouseDollAnimInstance();

	void PlayAttack_ReadyMontage();
	void PlayAttack_MeleeMontage();
	void PlayHitMontage();
	void PlayDeathMontage();
	
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack_Ready")
	//	UAnimMontage* Attack_ReadyMontage;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack_Melee")
	//	UAnimMontage* Attack_MeleeMontage;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit")
	//	UAnimMontage* HitMontage;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Death")
	//	UAnimMontage* DeathMontage;
	

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack_Ready", Meta = (AllowPrivateAccess = true))
	UAnimMontage* Attack_ReadyMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack_Melee", Meta = (AllowPrivateAccess = true))
	UAnimMontage* Attack_MeleeMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit", Meta = (AllowPrivateAccess = true))
	UAnimMontage* HitMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Death", Meta = (AllowPrivateAccess = true))
	UAnimMontage* DeathMontage;

	UFUNCTION()
	void AnimNotify_AttackHitCheck();


	
};
