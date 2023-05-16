// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GISS_Player.h"
#include "PlayerableCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerTestMapGM.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API APlayerTestMapGM : public AGameModeBase
{
	GENERATED_BODY()

public:
	APlayerTestMapGM();
	
	void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "GM")
		void SpawnWeapon(TSubclassOf<class AWeaponBase> weapon);
private :
	UGISS_Player* GameInstanceSubsystem;
	APlayerableCharacter* player;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
