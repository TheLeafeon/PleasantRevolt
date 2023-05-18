// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/Farmannequin.h"
#include "DrawDebugHelpers.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharMoveTest/FieldMonster/FarmannequinAnimInstance.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

AFarmannequin::AFarmannequin()
{

    Monster_HP = 18.0f;
    Monster_Power = 1.0f;
    Monster_Speed = 1.0f;
    Monster_Attack_Time = 0.0f;
    Monster_Attack_Delay = 5.0f;
    Monster_Knockback_Time = 0.0;
    isDie = false;

}

void AFarmannequin::BeginPlay()
{
    Super::BeginPlay();

    MyArea = FindClosestMonsterArea();
    MyAreaSize = MyArea->CollisionBox->GetScaledBoxExtent();
    MyAreaLocation = MyArea->GetActorLocation();

	AnimInstance = Cast<UFarmannequinAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance)
		return;

	AnimInstance->OnShotting.AddUObject(this, &AFarmannequin::ShottingCheck);
}

void AFarmannequin::Attack()
{
	if (!isPlayerAttackHit)
	{

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Attack"));
		
		AnimInstance->PlayAttackMontage();

		

	}
	isPlayerAttackHit = false;

	FTimerHandle AttackTimerHandle;
	FTimerDelegate AttackTimerDelegate = FTimerDelegate::CreateUObject(this, &AFarmannequin::AttackTimer);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, 4.0f, false);
}

void AFarmannequin::AttackTimer()
{
	FarmannequinOnAttackEnd.Broadcast();
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Fire"));
}

void AFarmannequin::ShottingCheck()
{
	Fire();
}

void AFarmannequin::DeathTimer()
{
	Destroy();
}

AFieldArea* AFarmannequin::FindClosestMonsterArea()
{
	TArray<AActor*> OverlappingActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFieldArea::StaticClass(), OverlappingActors);

	AFieldArea* ClosestArea = nullptr;
	FVector MouseDollLocation = GetActorLocation();

	float MinDistance = TNumericLimits<float>::Max();

	for (AActor* Actor : OverlappingActors)
	{
		AFieldArea* Area = Cast<AFieldArea>(Actor);
		if (Area != nullptr)
		{
			float Distance = FVector::Distance(MouseDollLocation, Area->GetActorLocation());
			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				ClosestArea = Area;
			}
		}
	}

	return ClosestArea;
}

float AFarmannequin::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float getDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (Monster_HP <= 0.0f)
	{
		return 0.0f;
	}

	if (getDamage > 0.0f)
	{
		Monster_HP -= getDamage;
	}

	if (!isDie)
	{
		isPlayerAttackHit = true;
		if (Monster_HP <= 0)
		{
			//Die(getDamage, DamgaeEvent, EventInstigator, DamageCauser);
			MyArea->numberOfMonstersDefeafed = MyArea->numberOfMonstersDefeafed + 1;

			Die(getDamage, DamageEvent, EventInstigator, DamageCauser);


		}
		else
		{
			OnHit(getDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
		}
	}

	return getDamage;
}

void AFarmannequin::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	Monster_HP = FMath::Min(0.0f, Monster_HP);
	isDie = true;

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();

	GetWorldTimerManager().ClearAllTimersForObject(this);
	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}


	FTimerHandle DeathTimerHandle;
	FTimerDelegate DeathTimerDelegate = FTimerDelegate::CreateUObject(this, &AFarmannequin::DeathTimer);
	GetWorldTimerManager().SetTimer(DeathTimerHandle, DeathTimerDelegate, 1.3f, false);
}

void AFarmannequin::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	if (DamageTaken > 0.0f)
	{
		isPlayerAttackHit = true;

		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
	}
}
