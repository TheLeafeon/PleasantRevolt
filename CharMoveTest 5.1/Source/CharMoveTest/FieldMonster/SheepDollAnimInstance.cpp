// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/SheepDollAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

USheepDollAnimInstance::USheepDollAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RUSHREADY_MONTAGE(TEXT("/Game/Monster/Animation/Montage/SheepDoll_RushReady_Montage.SheepDoll_RushReady_Montage"));
	if (RUSHREADY_MONTAGE.Succeeded())
	{
		Rush_ReadyMontage = RUSHREADY_MONTAGE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RUSH_MONTAGE(TEXT("/Game/Monster/Animation/Montage/SheepDoll_Rush_Montage.SheepDoll_Rush_Montage"));
	if (RUSH_MONTAGE.Succeeded())
	{
		RushMontage = RUSH_MONTAGE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HIT_MONTAGE(TEXT("/Game/Monster/Animation/Montage/SheepDoll_Hit_Montage.SheepDoll_Hit_Montage"));
	if (HIT_MONTAGE.Succeeded())
	{
		HitMontage = HIT_MONTAGE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DEATH_MONTAGE(TEXT("/Game/Monster/Animation/Montage/SheepDoll_Death_Montage.SheepDoll_Death_Montage"));
	if (DEATH_MONTAGE.Succeeded())
	{
		DeathMontage = DEATH_MONTAGE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> STUN_MONTAGE(TEXT("/Game/Monster/Animation/Montage/SheepDoll_Stun_Montage.SheepDoll_Stun_Montage"));
	if (STUN_MONTAGE.Succeeded())
	{
		DeathMontage = STUN_MONTAGE.Object;
	}
}

void USheepDollAnimInstance::PlayRush_ReadyMontage()
{
	Montage_Play(Rush_ReadyMontage, 1.0f);
}

void USheepDollAnimInstance::PlayRushMontage()
{
	Montage_Play(RushMontage, 1.0f);
}

void USheepDollAnimInstance::PlayHitMontage()
{
	Montage_Play(HitMontage, 1.0f);
}

void USheepDollAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage, 1.0f);
}

void USheepDollAnimInstance::PlayStunMontage()
{
	Montage_Play(StunMontage, 1.0f);
}
