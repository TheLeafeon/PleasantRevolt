// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharMoveTest/Boss/PD_FallDecal_Pawn.h"
#include "PD_LeftArm.generated.h"

UCLASS()
class CHARMOVETEST_API APD_LeftArm : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APD_LeftArm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Smash();
	void SmashWait();
	void BackSmash();
	void SetFallDecalPawn(APawn* Pawn);

private:
	FVector StartLocation;
	FVector TargetLocation;
	float StartTime;
	float Smash_TotalTime;
	float Restoration_TotalTime;

	bool IsSmash;
	bool Restoration;
	float CurrentTime;
	float Alpha;
	FVector NewLocation;

	APD_FallDecal_Pawn* FallDecalPawn;

	UPROPERTY(EditAnywhere, Category = "Status")
	float LeftArmHP;
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamgaeEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
public:
	UFUNCTION(BlueprintCallable)
		virtual float TakeDamage(float Damage, struct FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
