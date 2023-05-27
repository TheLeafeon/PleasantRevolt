// Fill out your copyright notice in the Description page of Project Settings.

#include "GISS_Player.h"
#include "PlayerableCharacter.h"
#include "PlayerTestMapGM.h"

UGISS_Player::UGISS_Player()
{
	WeaponInventory.Empty();
	//weaponInterface = nullptr;
	player = Cast<APlayerableCharacter>(StaticClass());
}

void UGISS_Player::GetWeapon(TSubclassOf<class AWeaponBase> weapon)
{
	if (!weapon)
		return;
	WeaponInventory.Add(weapon);

	APlayerTestMapGM* playerGM = GetWorld()->GetAuthGameMode<APlayerTestMapGM>();
	if (playerGM)
	{
		playerGM->SpawnWeapon(weapon);
	}
}

void UGISS_Player::GetWeaponActor(AWeaponBase* weapon)
{
	WeaponActors.Add(weapon);

}

void UGISS_Player::ResetWeaponActors()
{
	for (auto& element : WeaponActors)
	{
		element->Destroy();
	}
	WeaponActors.Empty();
}