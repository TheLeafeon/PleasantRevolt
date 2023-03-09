// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster_Base.generated.h"

UCLASS()
class CHARMOVETEST_API AMonster_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere,Category="MonsterInformation")
	int Monster_HP;
	UPROPERTY(EditAnywhere, Category = "MonsterInformation")
	int Monster_Power;
	UPROPERTY(EditAnywhere, Category = "MonsterInformation")
	int Monster_Speed;
	UPROPERTY(VisibleAnywhere, Category = "MonsterInformation")
	class USphereComponent* Monster_Attack_Distance;
	UPROPERTY(EditAnywhere, Category = "MonsterInformation")
	int Monster_Attack_Time;
	UPROPERTY(EditAnywhere, Category = "MonsterInformation")
	int Monster_Attack_Delay;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
