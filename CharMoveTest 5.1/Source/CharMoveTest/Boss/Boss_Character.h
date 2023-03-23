// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Boss_Character.generated.h"

UCLASS()
class CHARMOVETEST_API ABoss_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABoss_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, Category = "Status")
	float BossHP;
	UPROPERTY(EditAnywhere, Category = "Status")
	float MaxBossHP;

public:
	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamgaeEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	UFUNCTION()
	void HPHalf();
	UPROPERTY()
	TSubclassOf<class AActor> FallObj_Spawn_Blueprint;
	bool isSpawn;
};
