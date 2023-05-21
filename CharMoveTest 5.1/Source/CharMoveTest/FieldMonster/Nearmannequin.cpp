// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/Nearmannequin.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "CharMoveTest/FieldMonster/NearmannequinAIController.h"
#include "CharMoveTest/FieldMonster/NearmannequinAnimInstance.h"
#include "Engine/EngineTypes.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ANearmannequin::ANearmannequin()
{
	AIControllerClass = ANearmannequinAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Monster_HP = 15.0f;
	Monster_Power = 1.0f;
	Monster_Speed = 2.0f;
	//임시로 2.9
	Monster_Attack_Time = 2.9f;
	//임시로 짧게
	Monster_Attack_Delay = 1.0f;
	Monster_Knockback_Time = 0.5;
	isDie = false;


	//몬스터가 공격중인지
	isAttacking = false;

	AttackRange = 100.0f;
	AttackRadius = 50.0f;
}

void ANearmannequin::BeginPlay()
{
	Super::BeginPlay();

	

	MyArea = FindClosestMonsterArea();
	MyAreaSize = MyArea->CollisionBox->GetScaledBoxExtent();
	MyAreaLocation = MyArea->GetActorLocation();

	AnimInstance = Cast<UNearmannequinAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance)
		return;

	AnimInstance->OnAttackHitCheck.AddUObject(this, &ANearmannequin::AttackCheck);

	NearmannequinSpawnParticle();
}

AFieldArea* ANearmannequin::FindClosestMonsterArea()
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

void ANearmannequin::Attack_Ready()
{
	if (!isDie)
	{
		isAttacking = true;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("NearmannequinReady"));

		FTimerHandle AttackReadyTimerHandle;

		FTimerDelegate AttackReadyTimerDelegate = FTimerDelegate::CreateUObject(this, &ANearmannequin::AttackReadyTimer);
		GetWorldTimerManager().SetTimer(AttackReadyTimerHandle, AttackReadyTimerDelegate, Monster_Attack_Time, false);
	}
}

void ANearmannequin::Attack_Melee()
{
	
	
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("NearmannequinAttack"));

		AnimInstance->PlayAttack_MeleeMontage();

	FTimerHandle AttackTimerHandle;
	FTimerDelegate AttackTimerDelegate = FTimerDelegate::CreateUObject(this, &ANearmannequin::AttackTimer);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, Monster_Attack_Delay, false);
}

void ANearmannequin::AttackCheck()
{
	NearmannequinAttackParticle();

	FHitResult HitResult;
	TArray<FHitResult>HitResultArray;

	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

	GetWorld()->SweepMultiByChannel(HitResultArray, GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
#endif

	if (bResult)//뭔가 충돌이 있었는가?
	{
		for (const FHitResult& HitResults : HitResultArray)
		{
			AActor* HitActor = HitResults.GetActor();
			if (HitActor->IsA(APlayerableCharacter::StaticClass()))
			{
				APlayerableCharacter* OtherActor = Cast<APlayerableCharacter>(HitResult.GetActor());
				if (OtherActor)
				{
					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Nearmannequin Attack Hit"));
					
					NearmannequinApplyDamageEvent();
				}
			}
		}
	}

}

void ANearmannequin::AttackTimer()
{
	isAttacking = false;
	NearmannequinOnAttackEnd.Broadcast();
}

void ANearmannequin::AttackReadyTimer()
{
	Attack_Melee();
}

void ANearmannequin::DeathTimer()
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}
	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}
}

float ANearmannequin::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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
		
		if (Monster_HP <= 0)
		{
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

void ANearmannequin::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	if (DamageTaken > 0.0f)
	{
		

		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
	}
}

void ANearmannequin::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	Monster_HP = FMath::Min(0.0f, Monster_HP);
	isDie = true;

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();

	GetWorldTimerManager().ClearAllTimersForObject(this);

	FTimerHandle DeathTimerHandle;
	FTimerDelegate DeathTimerDelegate = FTimerDelegate::CreateUObject(this, &ANearmannequin::DeathTimer);
	GetWorldTimerManager().SetTimer(DeathTimerHandle, DeathTimerDelegate, 1.0f, false);
}
