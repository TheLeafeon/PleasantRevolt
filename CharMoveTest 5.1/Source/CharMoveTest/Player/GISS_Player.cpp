// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerableCharacter.h"
#include "GISS_Player.h"

UGISS_Player::UGISS_Player()
{
	WeaponInventory.Empty();
	weaponInterface = nullptr;
	player = Cast<APlayerableCharacter>(StaticClass());
}

void UGISS_Player::getWeapon(AWeaponBase* weapon)
{
	WeaponInventory.Add(weapon);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("getWeapon"));

	/*
	weaponInterface = Cast<IWeaponInterface>(getWeapon);
	if (weaponInterface)
	{
		weaponInterface->EquireWeapon();
	}
	*/
}