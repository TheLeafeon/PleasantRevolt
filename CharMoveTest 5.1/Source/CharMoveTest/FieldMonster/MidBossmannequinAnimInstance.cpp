// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/MidBossmannequinAnimInstance.h"

UMidBossmannequinAnimInstance::UMidBossmannequinAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> INRANGEATTACK_MONTAGE(TEXT("/Game/Monster/Animation/Montage/Midbossmannequin_Pattern_InRangeAttack_Montage.Midbossmannequin_Pattern_InRangeAttack_Montage"));
	if (INRANGEATTACK_MONTAGE.Succeeded())
	{
		InRangeAttackMontage = INRANGEATTACK_MONTAGE.Object;
	}
}

void UMidBossmannequinAnimInstance::PlayInRangeAttackMontage()
{
	Montage_Play(InRangeAttackMontage, 1.0f);
}

void UMidBossmannequinAnimInstance::AnimNotify_InRangeAttackHitCheck()
{
	OnInRangeAttackHitCheck.Broadcast();
}
