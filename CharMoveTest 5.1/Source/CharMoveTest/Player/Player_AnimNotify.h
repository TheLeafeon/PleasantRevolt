// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Player_AnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UPlayer_AnimNotify : public UAnimNotifyState
{
	GENERATED_BODY()
public :
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDurtion) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
