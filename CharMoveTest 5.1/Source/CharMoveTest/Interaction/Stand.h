// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharMoveTest/Interaction/DollRabbit.h"
#include "Stand.generated.h"

UCLASS()
class CHARMOVETEST_API AStand : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStand();


	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamgaeEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RotationStand();

	int StandState;

	UPROPERTY(EditAnywhere, Category = "DollRabbit")
	class ADollRabbit* DollRabbit;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
