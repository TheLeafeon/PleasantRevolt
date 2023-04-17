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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* BeHit_AnimMontage;


public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Rolling, Meta = (AllowPrivateAccess = true))
		float Roll_Animation_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Rolling, Meta = (AllowPrivateAccess = true))
		UAnimMontage* Rolling_AnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* NearWeapon1_AnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* NearWeapon2_AnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* NearWeapon3_AnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* Death_AnimMontage;

	//Ladder°ü·Ã ¸ùÅ¸ÁÖ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ladder, Meta = (AllowPrivateAccess = true))
	UAnimMontage* LadderMoveUp_AnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ladder, Meta = (AllowPrivateAccess = true))
	UAnimMontage* LadderMoveDown_AnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ladder, Meta = (AllowPrivateAccess = true))
	UAnimMontage* LadderMoveStart_AnimMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ladder, Meta = (AllowPrivateAccess = true))
	UAnimMontage* LadderMoveEnd_AnimMontage;
	void PlayLadderMoveUpMontage();
	void PlayLadderMoveDownMontage();
	void StopLadderMoveMontage();
	void PlayLadderMoveStartMontage();
	void PlayLadderMoveEndMontage();
};
