// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharMoveTest/Boss/PD_FallDecal_Pawn.h"
#include "PD_RightArm.generated.h"

UCLASS()
class CHARMOVETEST_API APD_RightArm : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APD_RightArm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Smash();
	void SmashWait();
	void BackSmash();
	void SetFallDecalPawn(APawn* Pawn);

private:
	FVector StartLocation;
	FVector TargetLocation;
	float StartTime;
	float Smash_TotalTime;
	float Restoration_TotalTime;

	bool IsSmash;
	bool Restoration;

	APD_FallDecal_Pawn* FallDecalPawn;
};
