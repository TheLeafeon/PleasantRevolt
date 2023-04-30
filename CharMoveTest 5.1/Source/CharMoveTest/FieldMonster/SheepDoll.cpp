// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/SheepDoll.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "CharMoveTest/FieldMonster/SheepDollAIController.h"
#include "CharMoveTest/FieldMonster/SheepDollAnimInstance.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


ASheepDoll::ASheepDoll()
{
	AIControllerClass = ASheepDollAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Monster_HP = 2.0f;
	Monster_Power = 1.0f;
	Monster_Speed = 1.0f;
	Monster_Attack_Time = 1.0f;
	Monster_Attack_Delay = 0.5f;
	Monster_Knockback_Time = 0.5;

	//플레이어에게 공격 당했는지
	isPlayerAttackHit = false;
	//몬스터가 공격중인지
	isAttacking = false;

	AttackRangeBoxSize = FVector(100.0f, 100.0f, 100.0f);

	AttackRangeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackRange"));

	AttackRangeBox->SetBoxExtent(AttackRangeBoxSize);
	AttackRangeBox->SetupAttachment(RootComponent);

}

void ASheepDoll::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Cast<USheepDollAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance)
		return;

	MyArea = FindClosestMonsterArea();
	MyAreaSize = MyArea->CollisionBox->GetScaledBoxExtent();
	MyAreaLocation = MyArea->GetActorLocation();
}

AFieldArea* ASheepDoll::FindClosestMonsterArea()
{
	TArray<AActor*> OverlappingActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFieldArea::StaticClass(), OverlappingActors);

	AFieldArea* ClosestArea = nullptr;
	FVector SheepDollLocation = GetActorLocation();

	float MinDistance = TNumericLimits<float>::Max();

	for (AActor* Actor : OverlappingActors)
	{
		AFieldArea* Area = Cast<AFieldArea>(Actor);
		if (Area != nullptr)
		{
			float Distance = FVector::Distance(SheepDollLocation, Area->GetActorLocation());
			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				ClosestArea = Area;
			}
		}
	}

	return ClosestArea;
}


void ASheepDoll::Rush_Ready()
{
	if (!isDie)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("SheepDoll_RushReady"));
		AnimInstance->PlayRush_ReadyMontage();

		FTimerHandle RushReadyTimerHandle;

		FTimerDelegate RushReadyTimerDelegate = FTimerDelegate::CreateUObject(this, &ASheepDoll::RushReadyTimer);
		GetWorldTimerManager().SetTimer(RushReadyTimerHandle, RushReadyTimerDelegate, 1.0f, false);
	}
}

void ASheepDoll::Stun()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("SheepDoll_Stun"));

	AnimInstance->PlayStunMontage();

	FTimerHandle StunTimerHandle;

	FTimerDelegate StunTimerDelegate = FTimerDelegate::CreateUObject(this, &ASheepDoll::StunTimer);
	GetWorldTimerManager().SetTimer(StunTimerHandle, StunTimerDelegate, 1.6f, false);
}

void ASheepDoll::RushReadyTimer()
{
	SheepDollOnAttackReadyEnd.Broadcast();
}

void ASheepDoll::StunTimer()
{
	//IsStunEnd();
	SheepDollStunEnd.Broadcast();
}


void ASheepDoll::DeathTimer()
{
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
}

float ASheepDoll::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

			SheepDollDeathKnockBack();
			Die(getDamage, DamageEvent, EventInstigator, DamageCauser);
			//Destroy();
		}
		else
		{
			OnHit(getDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
		}
	}

	return getDamage;
}

void ASheepDoll::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	if (DamageTaken > 0.0f)
	{
		isPlayerAttackHit = true;
		SheepDollKnockBack();
		AnimInstance->PlayHitMontage();

		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
	}
}

void ASheepDoll::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	Monster_HP = FMath::Min(0.0f, Monster_HP);
	isDie = true;

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();

	GetWorldTimerManager().ClearAllTimersForObject(this);

	AnimInstance->PlayDeathMontage();
	FTimerHandle DeathTimerHandle;
	FTimerDelegate DeathTimerDelegate = FTimerDelegate::CreateUObject(this, &ASheepDoll::DeathTimer);
	GetWorldTimerManager().SetTimer(DeathTimerHandle, DeathTimerDelegate, 1.0f, false);
}
