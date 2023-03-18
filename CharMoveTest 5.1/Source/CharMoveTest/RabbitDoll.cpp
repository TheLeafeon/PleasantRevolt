// Fill out your copyright notice in the Description page of Project Settings.


#include "RabbitDoll.h"
#include "TestCharacter.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Engine.h"


ARabbitDoll::ARabbitDoll()
{
	AIControllerClass = ARabbitDollAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Monster_HP = 2.0f;
	Monster_Power = 1.0f;
	Monster_Speed = 1.0f;
	Monster_Attack_Time = 1.0f;
	Monster_Attack_Delay = 0.5f;
	Monster_Knockback_Time = 0.5;
}