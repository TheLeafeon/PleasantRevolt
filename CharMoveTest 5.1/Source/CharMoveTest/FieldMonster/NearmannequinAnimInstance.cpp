// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/NearmannequinAnimInstance.h"
#include "NearmannequinAnimInstance.h"

UNearmannequinAnimInstance::UNearmannequinAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACKMELEE_MONTAGE(TEXT("/Game/Monster/Animation/Montage/Nearmannequin_AttackMelee_Montage.Nearmannequin_AttackMelee_Montage"));
	if (ATTACKMELEE_MONTAGE.Succeeded())
	{
		Attack_MeleeMontage = ATTACKMELEE_MONTAGE.Object;
	}
	
}

void UNearmannequinAnimInstance::PlayAttack_MeleeMontage()
{
	Montage_Play(Attack_MeleeMontage, 1.0f);
}

void UNearmannequinAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}
