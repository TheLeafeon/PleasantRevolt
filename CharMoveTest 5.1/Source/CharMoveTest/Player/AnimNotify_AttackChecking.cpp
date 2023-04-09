// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerableCharacter.h"
#include "AnimNotify_AttackChecking.h"

UAnimNotify_AttackChecking::UAnimNotify_AttackChecking()
{
}

void UAnimNotify_AttackChecking::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		APlayerableCharacter* Player = Cast<APlayerableCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->Enable_Attack_Enemy();
		}
	}
}

FString UAnimNotify_AttackChecking::GetNotifyName_Implementation() const
{
	return FString("AttackChecking");
}