// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "WeaponInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GISS_Player.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API UGISS_Player : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public :
	UGISS_Player();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
		void getWeapon(AWeaponBase* weapon);

	UPROPERTY(EditAnywhere, Category = "Weapons")
		TArray<AWeaponBase*> WeaponInventory;

private :
	IWeaponInterface* weaponInterface;
	class APlayerableCharacter* player;
};
