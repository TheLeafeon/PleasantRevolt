// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/MonsterBase.h"
#include "AITMonster.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API AAITMonster : public AMonsterBase
{
	GENERATED_BODY()
public:
	AAITMonster();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USphereComponent* CollisionSphere;
	
};
