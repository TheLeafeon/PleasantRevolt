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
