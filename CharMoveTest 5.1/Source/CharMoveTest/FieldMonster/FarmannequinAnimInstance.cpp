// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/FarmannequinAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UFarmannequinAnimInstance::UFarmannequinAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/Monster/Animation/Montage/Farmannequin_Attack_Montage.Farmannequin_Attack_Montage"));
	
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}

void UFarmannequinAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage, 1.0f);
}

void UFarmannequinAnimInstance::AnimNotify_Shotting()
{
	OnShotting.Broadcast();
}

