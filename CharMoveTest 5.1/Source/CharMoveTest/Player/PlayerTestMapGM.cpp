// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerTestMapGM.h"
#include "UObject/ConstructorHelpers.h"

APlayerTestMapGM::APlayerTestMapGM()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/PlayerTest/Player/BP_PlayerableCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void APlayerTestMapGM::SpawnWeapon(TSubclassOf<class AWeaponBase> weapon)
{
	if (weapon == nullptr)
		return;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AWeaponBase* weaponActor = GetWorld()->SpawnActor<AWeaponBase>(weapon, SpawnParams);
	// ���� �ν��Ͻ� ���� �ý��ۿ� ���͸� �����մϴ�.
	if (GameInstanceSubsystem)
	{
		GameInstanceSubsystem->GetWeaponActor(weaponActor);
}

void APlayerTestMapGM::BeginPlay()
{
	Super::BeginPlay();

	GameInstanceSubsystem = GetGameInstance()->GetSubsystem<UGISS_Player>();

	for (auto element : GameInstanceSubsystem->WeaponInventory)
	{
		SpawnWeapon(element);
	}
}

void APlayerTestMapGM::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EndPlayReason == EEndPlayReason::LevelTransition)
	{
		GameInstanceSubsystem->ResetWeaponActors();
	}
}