// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "InputChecking.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UInputChecking : public UAnimNotify
{
	GENERATED_BODY()
public:
	UInputChecking();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual FString GetNotifyName_Implementation() const override;
};
