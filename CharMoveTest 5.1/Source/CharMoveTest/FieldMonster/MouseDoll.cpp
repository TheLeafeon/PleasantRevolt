// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/MouseDoll.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "Engine/EngineTypes.h"
#include "CharMoveTest/FieldMonster/MouseDollAIController.h"
#include "CharMoveTest/FieldMonster/MouseDollAnimInstance.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


AMouseDoll::AMouseDoll()
{
	AIControllerClass = AMouseDollAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Monster_HP = 3.0f;
	Monster_Power = 1.0f;
	Monster_Speed = 2.0f;
	Monster_Attack_Time = 2.0f;
	Monster_Attack_Delay = 0.5f;
	Monster_Knockback_Time = 0.5;
	isDie = false;

	//플레이어에게 공격 당했는지
	isPlayerAttackHit = false;
	//몬스터가 공격중인지
	isAttacking = false;

	AttackRange = 200.0f;
	AttackRadius = 50.0f;
}

void AMouseDoll::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Cast<UMouseDollAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance)
		return;

	MyArea = FindClosestMonsterArea();
	MyAreaSize = MyArea->CollisionBox->GetScaledBoxExtent();
	MyAreaLocation = MyArea->GetActorLocation();

	AnimInstance->OnAttackHitCheck.AddUObject(this, &AMouseDoll::AttackCheck);
}

void AMouseDoll::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

AFieldArea* AMouseDoll::FindClosestMonsterArea()
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

void AMouseDoll::Attack_Ready()
{
	if (!isDie)
	{
		isAttacking = true;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("MouseDollReady"));

		AnimInstance->PlayAttack_ReadyMontage();

		FTimerHandle AttackReadyTimerHandle;

		FTimerDelegate AttackReadyTimerDelegate = FTimerDelegate::CreateUObject(this, &AMouseDoll::AttackReadyTimer);
		GetWorldTimerManager().SetTimer(AttackReadyTimerHandle, AttackReadyTimerDelegate, Monster_Attack_Time, false);
	}
}

void AMouseDoll::Attack_Melee()
{
	if (!isPlayerAttackHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("MouseDollAttack"));

		AnimInstance->PlayAttack_MeleeMontage();

	}

	isPlayerAttackHit = false;
	//공격 시간 타이머 핸들
	FTimerHandle AttackTimerHandle;
	FTimerDelegate AttackTimerDelegate = FTimerDelegate::CreateUObject(this, &AMouseDoll::AttackTimer);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, Monster_Attack_Delay, false);
}

void AMouseDoll::AttackCheck()
{
	
	MouseDollAttackParticle();

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
					isPlayerAttackHit = true;
					MouseDollApplyDamageEvent();
				}
			}
		}
	}
}

void AMouseDoll::AttackTimer()
{
	isAttacking = false;
	MouseDollOnAttackEnd.Broadcast();
}

void AMouseDoll::AttackReadyTimer()
{
	Attack_Melee();
}

float AMouseDoll::GetMouseDollHP()
{
	return Monster_HP;
}

void AMouseDoll::DeathTimer()
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

float AMouseDoll::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float getDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	MouseDollHitMaterial();
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
			MyArea->numberOfMonstersDefeafed = MyArea->numberOfMonstersDefeafed + 1;
			
			MouseDollDeathKnockBack();
			Die(getDamage, DamageEvent, EventInstigator, DamageCauser);
		}
		else
		{
			OnHit(getDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
		}
	}

	return getDamage;
}

void AMouseDoll::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	if (DamageTaken > 0.0f)
	{
		isPlayerAttackHit = true;
		
		MouseDollKnockBack();
		AnimInstance->PlayHitMontage();

		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
	}
}

void AMouseDoll::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	Monster_HP = FMath::Min(0.0f, Monster_HP);
	isDie = true;

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();

	GetWorldTimerManager().ClearAllTimersForObject(this);

	AnimInstance->PlayDeathMontage();
	FTimerHandle DeathTimerHandle;
	FTimerDelegate DeathTimerDelegate = FTimerDelegate::CreateUObject(this, &AMouseDoll::DeathTimer);
	GetWorldTimerManager().SetTimer(DeathTimerHandle, DeathTimerDelegate, 1.0f, false);
}
