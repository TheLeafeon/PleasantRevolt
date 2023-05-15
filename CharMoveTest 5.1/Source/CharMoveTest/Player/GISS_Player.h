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
		void GetWeapon(TSubclassOf<class AWeaponBase> weapon);
	UFUNCTION(BlueprintCallable, Category = "Weapons")
		void GetWeaponActor(AWeaponBase* weapon);
	void ResetWeaponActors();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
		TArray<TSubclassOf<class AWeaponBase>> WeaponInventory;
	UPROPERTY(EditAnywhere, Category = "Weapons")
		TArray<class AWeaponBase*> WeaponActors;
private :
	IWeaponInterface* weaponInterface;
	class APlayerableCharacter* player;
};
