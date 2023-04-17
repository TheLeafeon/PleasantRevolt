// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/MouseDollAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UMouseDollAnimInstance::UMouseDollAnimInstance()
{

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACKREADY_MONTAGE(TEXT("/Game/Monster/Animation/Montage/MouseDoll_AttackReady_Montage.MouseDoll_AttackReady_Montage"));
	if (ATTACKREADY_MONTAGE.Succeeded())
	{
		Attack_ReadyMontage = ATTACKREADY_MONTAGE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACKMELEE_MONTAGE(TEXT("/Game/Monster/Animation/Montage/MouseDoll_AttackMelee_Montage.MouseDoll_AttackMelee_Montage"));
	if (ATTACKMELEE_MONTAGE.Succeeded())
	{
		Attack_MeleeMontage = ATTACKMELEE_MONTAGE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HIT_MONTAGE(TEXT("/Game/Monster/Animation/Montage/MouseDoll_Hit_Montage.MouseDoll_Hit_Montage"));
	if (HIT_MONTAGE.Succeeded())
	{
		HitMontage = HIT_MONTAGE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DEATH_MONTAGE(TEXT("/Game/Monster/Animation/Montage/MouseDoll_Death_Montage.MouseDoll_Death_Montage"));
	if (DEATH_MONTAGE.Succeeded())
	{
		DeathMontage = DEATH_MONTAGE.Object;
	}

}

void UMouseDollAnimInstance::PlayAttack_ReadyMontage()
{
	Montage_Play(Attack_ReadyMontage, 1.0f);
}

void UMouseDollAnimInstance::PlayAttack_MeleeMontage()
{
	Montage_Play(Attack_MeleeMontage, 1.0f);
}

void UMouseDollAnimInstance::PlayHitMontage()
{
	Montage_Play(HitMontage, 1.0f);
}

void UMouseDollAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage, 1.0f);
}

void UMouseDollAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}



