// Fill out your copyright notice in the Description page of Project Settings.


#include "NearWeapon1.h"

ANearWeapon1::ANearWeapon1()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerAttackPower = 2.0f;
	WeaponMaxCombo = 4;
	WeaponAttackNearDistance = 1.0f;
	WeaponAttackTime = 1.0f;

	WeaponName = "NearWeapon1";
}

void ANearWeapon1::BeginPlay()
{
	Super::BeginPlay();
}

void ANearWeapon1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}