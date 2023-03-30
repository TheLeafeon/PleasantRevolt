// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponBase.h"
#include "AnimNotify_AttackChecking.h"

UAnimNotify_AttackChecking::UAnimNotify_AttackChecking()
{
}

void UAnimNotify_AttackChecking::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AWeaponBase* Weapon = Cast<AWeaponBase>(MeshComp->GetOwner());
		if (Weapon != NULL)
		{
			Weapon->MeleeAttacking();
		}
	}
}

FString UAnimNotify_AttackChecking::GetNotifyName_Implementation() const
{
	return FString("AttackChecking");
}