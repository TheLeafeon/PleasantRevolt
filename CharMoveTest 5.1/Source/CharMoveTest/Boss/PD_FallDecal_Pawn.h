// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CharMoveTest/Boss/Boss_Struct.h"
#include "PD_FallDecal_Pawn.generated.h"

UCLASS()
class CHARMOVETEST_API APD_FallDecal_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APD_FallDecal_Pawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPlasticDollInfo PlasticDollInfo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	FVector GetFallDecalPos();
};
