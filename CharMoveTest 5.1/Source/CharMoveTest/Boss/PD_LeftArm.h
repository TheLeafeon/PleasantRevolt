// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharMoveTest/Boss/PlasticDoll_Arm.h"
#include "PD_LeftArm.generated.h"

UCLASS()
class CHARMOVETEST_API APD_LeftArm : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APD_LeftArm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Smash();
	void SmashWait();
	void BackSmash();
};
