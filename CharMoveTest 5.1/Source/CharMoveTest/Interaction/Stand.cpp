// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Interaction/Stand.h"

// Sets default values
AStand::AStand()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StandState = 1;

}

float AStand::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float getDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (StandState <= 0.0f)
	{
		return 0.0f;
	}

	if (getDamage > 0.0f)
	{
		StandState -= getDamage;
	}

	if (StandState <= 0)
	{
		RotationStand();
		DollRabbit->FallRabbit();
		//OnHit(getDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
	}

	return getDamage;
}

void AStand::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	if (DamageTaken > 0.0f)
	{

		//ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);


	}
}

// Called when the game starts or when spawned
void AStand::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

