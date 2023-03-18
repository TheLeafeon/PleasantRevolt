// Fill out your copyright notice in the Description page of Project Settings.


#include "NearWeapon2.h"

ANearWeapon2::ANearWeapon2()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerAttackPower = 2.0f;
	WeaponMaxCombo = 5.0f;
	WeaponAttackNearDistance = 3.0f;
	WeaponAttackTime = 3.0f;
}

void ANearWeapon2::BeginPlay()
{
	Super::BeginPlay();
}

void ANearWeapon2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANearWeapon2::Attack()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("Weapon2 Attack"));
}
