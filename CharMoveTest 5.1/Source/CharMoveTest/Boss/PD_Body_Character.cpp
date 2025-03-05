// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PD_Body_Character.h"

// Sets default values
APD_Body_Character::APD_Body_Character() : IsHitOk(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BossIfo.BossHP = 10.0f;
}

// Called when the game starts or when spawned
void APD_Body_Character::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APD_Body_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APD_Body_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float APD_Body_Character::TakeDamage(float Damage, FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float getDamage = Super::TakeDamage(Damage, DamgaeEvent, EventInstigator, DamageCauser);

	if (!IsHitOk)
	{
		return 0.0f;
	}

	if (BossIfo.BossHP <= 0.0f)
	{
		return 0.0f;
	}

	if (getDamage > 0.0f)
	{
		BossIfo.BossHP -= getDamage;
	}

	if (BossIfo.BossHP <= 0)
	{
		Die(getDamage, DamgaeEvent, EventInstigator, DamageCauser);
	}
	else
	{
		OnHit(getDamage, DamgaeEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
	}

	return getDamage;
}

void APD_Body_Character::OnHit(float DamageTaken, FDamageEvent const& DamgaeEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	//애니메이션 들어갈 곳
	HitEffect();

	if (DamageTaken > 0.0f)
	{
		//ApplyDamageMomentum(DamageTaken, DamgaeEvent, PawnInstigator, DamageCauser);
	}
}

void APD_Body_Character::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	GetComponents<UParticleSystemComponent>(ParticleSystemComponents);
	for (UParticleSystemComponent* ParticleSystemComponent : ParticleSystemComponents)
	{
		ParticleSystemComponent->DestroyComponent();
	}


	//ABossAIController::PauseBehaviorTree();
	SetActorTickEnabled(false); //비헤이비어 트리를 중지

	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
	GetController()->Destroy();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APD_Body_Character::GoNextLevel, 3.0f, false);
}

void APD_Body_Character::GoNextLevel()
{
	NextLevelBP();
}