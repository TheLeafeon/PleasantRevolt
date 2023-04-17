// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/RabbitDoll.h"
#include "CharMoveTest/TestCharacter.h"
#include "Components/BoxComponent.h"
#include "CharMoveTest/FieldMonster/RabbitDollAIController.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


ARabbitDoll::ARabbitDoll()
{
	AIControllerClass = ARabbitDollAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Monster_HP = 2.0f;
	Monster_Power = 1.0f;
	Monster_Speed = 1.0f;
	Monster_Attack_Time = 1.0f;
	Monster_Attack_Delay = 0.5f;
	Monster_Knockback_Time = 0.5;

	AttackRangeBoxSize = FVector(100.0f, 100.0f, 100.0f);

	AttackRangeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackRange"));

	AttackRangeBox->SetBoxExtent(AttackRangeBoxSize);
	AttackRangeBox->SetupAttachment(GetMesh());

	
}

void ARabbitDoll::BeginPlay()
{
	Super::BeginPlay();

	MyArea = FindClosestMonsterArea();
	MyAreaSize = MyArea->CollisionBox->GetScaledBoxExtent();
	MyAreaLocation = MyArea->GetActorLocation();


	//Rabbit�� ���������� �ڶ󳪵��� ����
	FVector RabbitDollSpawnStartLocation = GetActorLocation();
	StartZLocation = RabbitDollSpawnStartLocation.Z;
	RabbitDollSpawnStartLocation.Z = RabbitDollSpawnStartLocation.Z - 200.0f;
	SetActorLocation(RabbitDollSpawnStartLocation);

	SetActorEnableCollision(false);

	FTimerDelegate GirlDollSpawnMoveUpDelegate = FTimerDelegate::CreateUObject(this, &ARabbitDoll::RabbitDollSpawnEffect);
	GetWorldTimerManager().SetTimer(RabbitDollSpawnMoveUpHandle, GirlDollSpawnMoveUpDelegate, 0.01f, true);
}



AFieldArea* ARabbitDoll::FindClosestMonsterArea()
{
	TArray<AActor*> OverlappingActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFieldArea::StaticClass(), OverlappingActors);

	AFieldArea* ClosestArea = nullptr;
	FVector GirlDollLocation = GetActorLocation();

	float MinDistance = TNumericLimits<float>::Max();

	for (AActor* Actor : OverlappingActors)
	{
		AFieldArea* Area = Cast<AFieldArea>(Actor);
		if (Area != nullptr)
		{
			float Distance = FVector::Distance(GirlDollLocation, Area->GetActorLocation());
			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				ClosestArea = Area;
			}
		}
	}

	return ClosestArea;
}

void ARabbitDoll::RabbitDollSpawnEffect()
{
	FVector RabbitDollSpawnStartLocation = GetActorLocation();
	float CurrentZ = RabbitDollSpawnStartLocation.Z;
	float TargetZ = StartZLocation; // ��ǥ ��ġ
	float Speed = 10.f; // �̵� �ӵ� (1�ʿ� 1000��ŭ �̵�)

	float DeltaZ = Speed * GetWorld()->GetDeltaSeconds();
	float NewZ = FMath::FInterpTo(CurrentZ, TargetZ, GetWorld()->GetDeltaSeconds(), Speed);
	RabbitDollSpawnStartLocation.Z = NewZ;

	SetActorLocation(RabbitDollSpawnStartLocation);

	if (FMath::IsNearlyEqual(NewZ, TargetZ, 0.1f)) // ��ǥ ��ġ�� �������� �� Ÿ�̸� ����
	{
		SetActorEnableCollision(true);
		GetWorld()->GetTimerManager().ClearTimer(RabbitDollSpawnMoveUpHandle);
	}
}



float ARabbitDoll::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

	if (Monster_HP <= 0)
	{
		MyArea->numberOfMonstersDefeafed = MyArea->numberOfMonstersDefeafed + 1;
		//Die(getDamage, DamgaeEvent, EventInstigator, DamageCauser);
		Destroy();
	}
	else
	{
		OnHit(getDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
	}

	return getDamage;
}

void ARabbitDoll::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	if (DamageTaken > 0.0f)
	{
		RabbitDollKnockBack();

		/*FVector KnockbackDirection = PawnInstigator->GetActorLocation() - GetActorLocation();
		KnockbackDirection.Normalize();

		GetMesh()->AddImpulse(KnockbackDirection * 100, NAME_None, true);*/

		//GirlDollOnAttackEnd.Broadcast();
		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);

	}
}
