// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterBase.h"
#include "RabbitDollAIController.h"
#include "RabbitDoll.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API ARabbitDoll : public AMonsterBase
{
	GENERATED_BODY()

public:

	ARabbitDoll();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USphereComponent* CollisionSphere;

};
