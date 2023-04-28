// Fill out your copyright notice in the Description page of Project Settings.


#include "NearWeapon2.h"

ANearWeapon2::ANearWeapon2()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerAttackPower = 3.0f;
	WeaponMaxCombo = 2;
	WeaponAttackNearDistance = 3.0f;
	WeaponAttackTime = 3.0f;

	WeaponName = "NearWeapon2";
}

void ANearWeapon2::BeginPlay()
{
	Super::BeginPlay();
}

void ANearWeapon2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}