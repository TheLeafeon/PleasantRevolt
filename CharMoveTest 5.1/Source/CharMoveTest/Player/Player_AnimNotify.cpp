// Fill out your copyright notice in the Description page of Project Settings.

#include "Player_AnimNotify.h"
#include "PlayerableCharacter.h"

void UPlayer_AnimNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDurtion)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		APlayerableCharacter* Player = Cast<APlayerableCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->bisAttack = false;
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("CanNextCombo"));
			Player->Attack_Melee_End();
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
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("EndAttack"));
		}
	}
}
