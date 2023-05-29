// Fill out your copyright notice in the Description page of Project Settings.


#include "NearWeapon3.h"

ANearWeapon3::ANearWeapon3()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerAttackPower = 2.0f;
	WeaponMaxCombo = 5;
	WeaponAttackNearDistance = 1.0f;
	WeaponAttackTime = 1.0f;

	WeaponName = "NearWeapon3";
}