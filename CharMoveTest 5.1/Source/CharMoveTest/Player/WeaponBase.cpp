// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "PlayerableCharacter.h"
#include "SampleEnemy.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	TraceRadius = 120.0f;

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

	//bool isHit =  GetWorld()->LineTraceMultiByChannel(HitResults, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, CollisionParams);

	bool isHit = GetWorld()->SweepMultiByChannel(HitResults, StartLocation, EndLocation, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(TraceRadius), CollisionParams);

	if (isHit)
	{
		for (const FHitResult& HitResult : HitResults)
		{
			AActor* HitActor = HitResult.GetActor();
			ASampleEnemy* HitEnemy = Cast<ASampleEnemy>(HitActor);
			
			if (!HitEnemy || DetectedActors.Contains(HitEnemy))
				continue;
			else
			{
				DetectedActors.Add(HitEnemy);
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "Bot Damage");
			}
		}
	}
}