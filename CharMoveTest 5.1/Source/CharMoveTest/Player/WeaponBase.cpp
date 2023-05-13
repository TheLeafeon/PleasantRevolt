// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "SampleEnemy.h"
#include "PlayerableCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "CharMoveTest/FieldMonster/MonsterBase.h"
#include "CharMoveTest/Boss/Boss_Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Self = this;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> ATTACKENEMYPARTICLE(TEXT("/Game/PlayerTest/PlayerFX/Particles/UPDATE_1_3/P_Web_Hit_05.P_Web_Hit_05"));
	if(ATTACKENEMYPARTICLE.Succeeded())
	{
		AttackEnemyParticle = ATTACKENEMYPARTICLE.Object;
	}

	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	RootComponent = _RootComponent;

	NearWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SampleMesh"));
	NearWeaponMesh->SetupAttachment(RootComponent);

	PlayerAttackPower = 0.0f;
	WeaponMaxCombo = 0;
	WeaponAttackNearDistance = 0.0f;
	WeaponAttackTime = 0;
	WeaponName = "";
	isAttacking = false;

	TraceInterval = 0.02f;
	TraceLastTime = TraceInterval;

	MyPawn = Cast<APlayerableCharacter>(StaticClass());

	TraceRadius = 60.0f;

	CollisionParams.bTraceComplex = true;
	CollisionParams.bReturnPhysicalMaterial = false;
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.AddIgnoredActor(MyPawn);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isAttacking)
	{
		if (TraceLastTime >= TraceInterval)
		{
			WeaponTrace();
			TraceLastTime = 0.0f;
		}
		else
			TraceLastTime += DeltaTime;
	}
}

void AWeaponBase::Enable_Attack_Enemy()
{
	isAttacking = true;
}

void AWeaponBase::Disable_Attack_Enemy()
{
	isAttacking = false;
	DetectedActors.Empty();
}

void AWeaponBase::WeaponTrace()
{
	TArray<FHitResult> HitResults;
	FVector StartLocation = NearWeaponMesh->GetSocketLocation("StartSocket");
	FVector EndLocation = NearWeaponMesh->GetSocketLocation("EndSocket");

	bool isHit = GetWorld()->SweepMultiByChannel(HitResults, StartLocation, EndLocation, FQuat::Identity, ECC_Camera, FCollisionShape::MakeSphere(TraceRadius), CollisionParams);

	if (isHit)
	{
		for (const FHitResult& HitResult : HitResults)
		{
			UPrimitiveComponent* HitComponent = HitResult.GetComponent();
			AMonsterBase* HitMonster = nullptr;
			ABoss_Character* HitBoss = nullptr;

			if (HitComponent)
			{
				HitMonster = Cast<AMonsterBase>(HitComponent->GetOwner());
				HitBoss = Cast<ABoss_Character>(HitComponent->GetOwner());
			}
			
			if(HitMonster)
				DuplicationEnemy(HitMonster);
			if (HitBoss)
				DuplicationEnemy(HitBoss);
		}
	}
}

void AWeaponBase::DuplicationEnemy(ACharacter* Enemy)
{
	if (!Enemy || DetectedActors.Contains(Enemy))
		return;
	else
	{
		DetectedActors.Add(Enemy);

		UGameplayStatics::ApplyDamage(Enemy, PlayerAttackPower, NULL, this, UDamageType::StaticClass());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), AttackEnemyParticle, GetActorLocation());
	}
}

void AWeaponBase::EquireWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("getWeapon"));
}
