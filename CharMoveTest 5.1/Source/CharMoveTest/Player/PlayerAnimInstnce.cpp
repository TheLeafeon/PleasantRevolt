// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstnce.h"

UPlayerAnimInstnce::UPlayerAnimInstnce()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Rolling_MONTAGE(TEXT("/Game/PlayerTest/Player/Animations/Dive_Roll_Montage.Dive_Roll_Montage"));
	if (Rolling_MONTAGE.Succeeded())
	{
		Rolling_AnimMontage = Rolling_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> NEARWEAPON1_MONTGE(TEXT("/Game/PlayerTest/Player/Animations/Nearweapon1_Combo_Montage.Nearweapon1_Combo_Montage"));
	if (NEARWEAPON1_MONTGE.Succeeded())
	{
		NearWeapon1_AnimMontage = NEARWEAPON1_MONTGE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> NEARWEAPON2_MONTGE(TEXT("/Game/PlayerTest/Player/Animations/NearWeapon3_Combo_Montage.NearWeapon3_Combo_Montage"));
	if (NEARWEAPON2_MONTGE.Succeeded())
	{
		NearWeapon2_AnimMontage = NEARWEAPON2_MONTGE.Object;
	}
	//static ConstructorHelpers::FObjectFinder<UAnimMontage> BEHIT_MONTAGE(TEXT("));
	//if (BEHIT_MONTAGE.Succeeded())
	//{
	//	BeHit_AnimMontage = BEHIT_MONTAGE.Object;
	//}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DEATH_MONTAGE(TEXT("/Game/PlayerTest/Player/Animations/Player_Death_Montage.Player_Death_Montage"));
	if (DEATH_MONTAGE.Succeeded())
	{
		Death_AnimMontage = DEATH_MONTAGE.Object;
	}
}

void UPlayerAnimInstnce::PlayRollingMontage()
{
	Montage_Play(Rolling_AnimMontage, 1.0f);
}

void UPlayerAnimInstnce::PlayBeHitMontage()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Hit"));
}

void UPlayerAnimInstnce::PlayDeathMontage()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Dead"));
}
