// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_AttackChecking.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UAnimNotify_AttackChecking : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_AttackChecking();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual FString GetNotifyName_Implementation() const override;
};
