// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "NearWeapon2.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API ANearWeapon2 : public AWeaponBase
{
	GENERATED_BODY()
public:
	ANearWeapon2();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
