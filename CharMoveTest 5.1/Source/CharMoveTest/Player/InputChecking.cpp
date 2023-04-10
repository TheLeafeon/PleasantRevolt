// Fill out your copyright notice in the Description page of Project Settings.

#include "InputChecking.h"
#include "PlayerableCharacter.h"


UInputChecking::UInputChecking()
{
}
void UInputChecking::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		APlayerableCharacter* Player = Cast<APlayerableCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->bisAttack = false;
			//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("NotifyBegin"));
		}
	}
}

FString UInputChecking::GetNotifyName_Implementation() const
{
	return FString("InputChecking");
}
