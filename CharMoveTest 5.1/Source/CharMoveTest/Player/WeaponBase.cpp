// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "PlayerableCharacter.h"
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

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetBoxExtent(FVector(3.f, 3.f, 3.f));
	WeaponCollision->SetupAttachment(NearWeaponMesh);

	PlayerAttackPower = 0.0f;
	WeaponMaxCombo = 0;
	WeaponAttackNearDistance = 0.0f;
	WeaponAttackTime = 0;

	MyPawn = Cast<APlayerableCharacter>(StaticClass());
	isAttacking = false;
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

}

void AWeaponBase::StartAttack()
{
	float AttackAnimDurtion = MyPawn->PlayAnimMontage(MyPawn->Get_Attack_AnimMontage());

	isAttacking = true;

	FTimerHandle TimerHandle_StopAttack;
	GetWorldTimerManager().SetTimer(TimerHandle_StopAttack, this, &AWeaponBase::StopAttack, AttackAnimDurtion, false);
}

void AWeaponBase::StopAttack()
{
	MyPawn->StopAnimMontage(MyPawn->Get_Attack_AnimMontage());
	isAttacking = false;
}

void AWeaponBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	APlayerableCharacter* MyPlayer = Cast<APlayerableCharacter>(StaticClass());


	if (OtherActor->IsA(AActor::StaticClass()) && !OtherActor->IsA(APlayerableCharacter::StaticClass())/*&& isAttacking == true*/)
	{
		UGameplayStatics::ApplyDamage(OtherActor, PlayerAttackPower, NULL, this, UDamageType::StaticClass());
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Bot Damage");
	}
}