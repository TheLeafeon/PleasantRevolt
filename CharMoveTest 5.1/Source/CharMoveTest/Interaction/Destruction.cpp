// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Interaction/Destruction.h"

// Sets default values
ADestruction::ADestruction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADestruction::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestruction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ADestruction::TakeDamage(float Damage, FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float getDamage = Super::TakeDamage(Damage, DamgaeEvent, EventInstigator, DamageCauser);

	if (getDamage > 0.0f)
	{
		OnHit(getDamage, DamgaeEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
	}

	return getDamage;
}

void ADestruction::OnHit(float DamageTaken, struct FDamageEvent const& DamgaeEvent, class APawn* PawnInstigator, class AActor* DamageCauser)
{
	Destroy();
}