// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FarmannequinAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackCheckDelegate);
/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UFarmannequinAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFarmannequinAnimInstance();

	void PlayAttackMontage();

	FOnAttackCheckDelegate OnShotting;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;

	UFUNCTION()
		void AnimNotify_Shotting();
	
};
