// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerableCharacter.h"
#include "Player_AnimNotify.h"

void UPlayer_AnimNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDurtion)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		APlayerableCharacter* Player = Cast<APlayerableCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->bisAttack = true;
		}
	}
}

void UPlayer_AnimNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		APlayerableCharacter* Player = Cast<APlayerableCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->Attack_Melee_End();
			Player->bisAttack = false;
		}
	}
}
