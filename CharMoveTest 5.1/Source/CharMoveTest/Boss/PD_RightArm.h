// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CharMoveTest/Boss/PD_FallDecal_Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PrimitiveComponent.h"
#include "PD_RightArm.generated.h"

UCLASS()
class CHARMOVETEST_API APD_RightArm : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APD_RightArm();

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
	FVector EndLocation;

	APD_FallDecal_Pawn* FallDecalPawn;

	UPROPERTY(EditAnywhere, Category = "Status")
	float RightArmHP;
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamgaeEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser) override;

	//UFUNCTION()
	//void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	APawn* Player;
	bool IsAttack;

public:
	UPROPERTY(BlueprintReadWrite)
	UPrimitiveComponent* CollisionComponent;
	UFUNCTION(BlueprintImplementableEvent)
	void SetWaitAni(bool value);
	UFUNCTION(BlueprintImplementableEvent)
	void SetAttackAni(bool value);
	UFUNCTION(BlueprintImplementableEvent)
	void HitEffect();
};
