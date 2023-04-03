// Fill out your copyright notice in the Description page of Project Settings.

#include "SampleEnemy.h"
#include "PlayerableCharacter.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ASampleEnemy::ASampleEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	RootComponent = _RootComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SampleMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	hp = 100.0f;
}

// Called when the game starts or when spawned
void ASampleEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASampleEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA(APlayerableCharacter::StaticClass()))
	{
	}
}

float ASampleEnemy::TakeDamage(float Damage, FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float getDamage = Super::TakeDamage(Damage, DamgaeEvent, EventInstigator, DamageCauser);
	
	if (hp <= 0.0f)
		return 0.0f;

	if (getDamage > 0.f)
	{
		hp -= getDamage;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Debug %d"), hp));

	return 0.0f;
}

// Called every frame
void ASampleEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

