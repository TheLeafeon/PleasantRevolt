// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstnce.h"

UPlayerAnimInstnce::UPlayerAnimInstnce()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Rolling_MONTAGE(TEXT("/Game/PlayerTest/Player/Animations/Rolling_Montage.Rolling_Montage"));
	if (Rolling_MONTAGE.Succeeded())
	{
		Rolling_AnimMontage = Rolling_MONTAGE.Object;
	}
	Roll_Animation_Speed = 1.0f;

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

	static ConstructorHelpers::FObjectFinder<UAnimMontage> LADDERMOVEUP_MONTAGE(TEXT("/Game/Interaction/Animation/ModularAnimalKnightsPolyart/Animations/LadderUp_Montage.LadderUp_Montage"));
	if (LADDERMOVEUP_MONTAGE.Succeeded())
	{
		LadderMoveUp_AnimMontage = LADDERMOVEUP_MONTAGE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> LADDERMOVEDOWN_MONTAGE(TEXT("/Game/Interaction/Animation/ModularAnimalKnightsPolyart/Animations/LadderDown_Montage.LadderDown_Montage"));
	if (LADDERMOVEDOWN_MONTAGE.Succeeded())
	{
		LadderMoveDown_AnimMontage = LADDERMOVEDOWN_MONTAGE.Object;
	}
}

void UPlayerAnimInstnce::PlayRollingMontage()
{
	Montage_Play(Rolling_AnimMontage, Roll_Animation_Speed);
}

void UPlayerAnimInstnce::PlayBeHitMontage()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Hit"));
}

void UPlayerAnimInstnce::PlayDeathMontage()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Dead"));
}

void UPlayerAnimInstnce::PlayLadderMoveUpMontage()
{
	Montage_Play(LadderMoveUp_AnimMontage, 1.0f);
}

void UPlayerAnimInstnce::PlayLadderMoveDownMontage()
{
	Montage_Play(LadderMoveDown_AnimMontage, 1.0f);
}

void UPlayerAnimInstnce::StopLadderMoveMontage()
{
	Montage_Stop(0.0f, LadderMoveDown_AnimMontage);
	Montage_Stop(0.0f, LadderMoveUp_AnimMontage);
}