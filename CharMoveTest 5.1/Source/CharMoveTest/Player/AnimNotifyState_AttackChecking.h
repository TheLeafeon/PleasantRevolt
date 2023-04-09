// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_AttackChecking.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UAnimNotifyState_AttackChecking : public UAnimNotifyState
{
	GENERATED_BODY()
public :
	UAnimNotifyState_AttackChecking();

	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	
	virtual FString GetNotifyName_Implementation() const override;
};
