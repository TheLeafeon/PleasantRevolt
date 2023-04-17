// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/DoveDollAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UDoveDollAnimInstance::UDoveDollAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/Monster/Animation/Montage/DoveDoll_Attack_Montage.DoveDoll_Attack_Montage"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HIT_MONTAGE(TEXT("/Game/Monster/Animation/Montage/DoveDoll_Hit_Montage.DoveDoll_Hit_Montage"));
	if (HIT_MONTAGE.Succeeded())
	{
		HitMontage = HIT_MONTAGE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DEATH_MONTAGE(TEXT("/Game/Monster/Animation/Montage/DoveDoll_Death_Montage.DoveDoll_Death_Montage"));
	if (DEATH_MONTAGE.Succeeded())
	{
		DeathMontage = DEATH_MONTAGE.Object;
	}
}

void UDoveDollAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage, 1.0f);
}

void UDoveDollAnimInstance::PlayHitMontage()
{
	Montage_Play(HitMontage, 1.0f);
}

void UDoveDollAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage, 1.0f);
}
