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

	static ConstructorHelpers::FObjectFinder<UAnimMontage> NEARWEAPON1_MONTGE(TEXT("/Game/PlayerTest/Player/Animations/NearWeapon1_Attack_Montage.NearWeapon1_Attack_Montage"));
	if (NEARWEAPON1_MONTGE.Succeeded())
	{
		NearWeapon1_AnimMontage = NEARWEAPON1_MONTGE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> NEARWEAPON2_MONTGE(TEXT("/Game/PlayerTest/Player/Animations/NearWeapon2_Attack_Montage.NearWeapon2_Attack_Montage"));
	if (NEARWEAPON2_MONTGE.Succeeded())
	{
		NearWeapon2_AnimMontage = NEARWEAPON2_MONTGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> BEHIT_MONTAGE(TEXT("/Game/PlayerTest/Player/Animations/Player_Hit_Montage.Player_Hit_Montage"));
	if (BEHIT_MONTAGE.Succeeded())
	{
		BeHit_AnimMontage = BEHIT_MONTAGE.Object;
	}

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
	static ConstructorHelpers::FObjectFinder<UAnimMontage> LADDERMOVESTART_MONTAGE(TEXT("/Game/Interaction/Animation/ModularAnimalKnightsPolyart/Animations/LadderStart_Montage.LadderStart_Montage"));
	if (LADDERMOVESTART_MONTAGE.Succeeded())
	{
		LadderMoveStart_AnimMontage = LADDERMOVESTART_MONTAGE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> LADDERMOVEEND_MONTAGE(TEXT("/Game/Interaction/Animation/ModularAnimalKnightsPolyart/Animations/LadderEnd_Montage.LadderEnd_Montage"));
	if (LADDERMOVEEND_MONTAGE.Succeeded())
	{
		LadderMoveEnd_AnimMontage = LADDERMOVEEND_MONTAGE.Object;
	}
}

void UPlayerAnimInstnce::PlayRollingMontage()
{
	Montage_Play(Rolling_AnimMontage, Roll_Animation_Speed);
}

void UPlayerAnimInstnce::PlayBeHitMontage()
{
	Montage_Play(BeHit_AnimMontage, 1.0f);
}

void UPlayerAnimInstnce::PlayDeathMontage()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Dead"));
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
	Montage_Stop(0.0f, LadderMoveStart_AnimMontage);
	Montage_Stop(0.0f, LadderMoveDown_AnimMontage);
	Montage_Stop(0.0f, LadderMoveUp_AnimMontage);
}

void UPlayerAnimInstnce::PlayLadderMoveStartMontage()
{
	Montage_Play(LadderMoveStart_AnimMontage, 1.0f);
}

void UPlayerAnimInstnce::PlayLadderMoveEndMontage()
{
	Montage_Play(LadderMoveEnd_AnimMontage, 1.0f);
}
