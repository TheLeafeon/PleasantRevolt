// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstnce.h"

UPlayerAnimInstnce::UPlayerAnimInstnce()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SAMPLE_MONTAGE(TEXT("/Game/PlayerTest/Samples/RetargetAnimation/Rolling_Montage.Rolling_Montage"));
	if (SAMPLE_MONTAGE.Succeeded())
	{
		Sample = SAMPLE_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> MELEEATTACK_MONTAGE(TEXT("/Game/PlayerTest/Samples/RetargetAnimation/Standing_Melee_Attack_Montage.Standing_Melee_Attack_Montage"));
	if (MELEEATTACK_MONTAGE.Succeeded())
	{
		Attack_AnimMontage = MELEEATTACK_MONTAGE.Object;
	}

	//static ConstructorHelpers::FObjectFinder<UAnimMontage> BEHIT_MONTAGE(TEXT("));
	//if (BEHIT_MONTAGE.Succeeded())
	//{
	//	BeHit_AnimMontage = BEHIT_MONTAGE.Object;
	//}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DEATH_MONTAGE(TEXT("/Game/PlayerTest/Samples/RetargetAnimation/Dying_Montage.Dying_Montage"));
	if (DEATH_MONTAGE.Succeeded())
	{
		Death_AnimMontage = DEATH_MONTAGE.Object;
	}
}

void UPlayerAnimInstnce::PlaySampleMontage()
{
	Montage_Play(Sample, 1.0f);
}

void UPlayerAnimInstnce::PlayMeleeAttackMontage()
{
	Montage_Play(Attack_AnimMontage, 1.0f);
}

void UPlayerAnimInstnce::PlayBeHitMontage()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Hit"));
}

void UPlayerAnimInstnce::PlayDeathMontage()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Dead"));
}
