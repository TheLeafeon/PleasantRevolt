// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerableCharacter.h"
#include "AnimNotifyState_AttackChecking.h"

UAnimNotifyState_AttackChecking::UAnimNotifyState_AttackChecking()
{
}

void UAnimNotifyState_AttackChecking::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		APlayerableCharacter* Player = Cast<APlayerableCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->Enable_Attack_Enemy();
		}
	}
}

void UAnimNotifyState_AttackChecking::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		APlayerableCharacter* Player = Cast<APlayerableCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->Disable_Attack_Enemy();
		}
	}
}

FString UAnimNotifyState_AttackChecking::GetNotifyName_Implementation() const
{
	return FString("AttackChecking");
}