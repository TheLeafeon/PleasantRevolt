// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/BD_Boss_Character.h"

// Sets default values
ABD_Boss_Character::ABD_Boss_Character() : BossHP(20.0f), MaxBossHP(20.0f), isSpawn(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABD_Boss_Character::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerableCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

// Called every frame
void ABD_Boss_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABD_Boss_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABD_Boss_Character::TakeDamage(float Damage, FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float getDamage = Super::TakeDamage(Damage, DamgaeEvent, EventInstigator, DamageCauser);

	if (BossHP <= 0.0f)
	{
		return 0.0f;
	}		

	if (getDamage > 0.0f)
	{
		BossHP -= getDamage;
	}

	if (BossHP <= 0)
	{
		Die(getDamage, DamgaeEvent, EventInstigator, DamageCauser);
	}
	else
	{
		OnHit(getDamage, DamgaeEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
	}

	return getDamage;
}

void ABD_Boss_Character::OnHit(float DamageTaken, FDamageEvent const& DamgaeEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	if (DamageTaken > 0.0f)
	{
		//데미지 받고 뒤로 밀림?
		//ApplyDamageMomentum(DamageTaken, DamgaeEvent, PawnInstigator, DamageCauser);

		HitEffect();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("!"));

		if ((BossHP <= MaxBossHP / 2) && isSpawn == false)
		{
			HPHalf();
			isSpawn = true;
		}
	}
}

void ABD_Boss_Character::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	Player->IsStop = true;
	SetActorTickEnabled(false); //비헤이비어 트리를 중지

	//파티클 삭제
	GetComponents<UParticleSystemComponent>(ParticleSystemComponents);
	for (UParticleSystemComponent* ParticleSystemComponent : ParticleSystemComponents)
	{
		ParticleSystemComponent->DestroyComponent();
	}

	USoundBase* Sound = LoadObject<USoundBase>(nullptr, TEXT("/Game/Boss/1Stage/Sound/bear_scream.bear_scream"), nullptr, LOAD_None, nullptr);
	UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());

	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
	SpawnDanger->Destroy();
	GetController()->Destroy();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle2, this, &ABD_Boss_Character::SpawnArm, 3.0f, false);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABD_Boss_Character::GoNextLevel, 5.5f, false);
}

void ABD_Boss_Character::HPHalf()
{
	//충돌체 스폰기 스폰
	if (FallObj_Spawn_Blueprint)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			FRotator rotator;
			FVector  SpawnLocation = FVector(7970.0f, 10270.0f, -6741.8f);//GetActorLocation(); //보스 스폰 액터 자리에 소환? 아님 보스 근처에서 소환?

			SpawnDanger = world->SpawnActor<AActor>(FallObj_Spawn_Blueprint, SpawnLocation, rotator, SpawnParams);
		}
	}
}

void ABD_Boss_Character::SpawnArm()
{
	UWorld* world = GetWorld();
	if (world)
	{
		world->SpawnActor<AActor>(Arm_Blueprint, FVector(9428.0f, 12150.0f, -5950.0f), FRotator(0.0f, 215.0f, 0.0f));
	}
}

void ABD_Boss_Character::GoNextLevel()
{
	Player->IsStop = false;
	//UGameplayStatics::OpenLevel(this, FName("stage2_start_cinematic"));
	NextLevelBP();
}