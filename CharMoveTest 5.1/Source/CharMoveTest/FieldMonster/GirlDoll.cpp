// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/GirlDoll.h"
#include "CharMoveTest/CharMoveTest.h"
#include "Components/BoxComponent.h"
#include "CharMoveTest/FieldMonster/GirlDollAIController.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Engine.h"
#include <CharMoveTest/CharMoveTest.h>

AGirlDoll::AGirlDoll()
{

	AIControllerClass = AGirlDollAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


	Monster_HP = 3.0f;
	Monster_Power = 1.0f;
	Monster_Speed = 2.0f;
	Monster_Attack_Time = 1.0f;
	Monster_Attack_Delay = 0.5f;
	Monster_Knockback_Time = 0.5;
	AttackRangeBoxSize = FVector(100.0f, 100.0f, 100.0f);

	AttackRangeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackRange"));

	AttackRangeBox->SetBoxExtent(AttackRangeBoxSize);
	AttackRangeBox->SetupAttachment(GetMesh());

	isAttackDuring = false;
	isAttackReady = false;

	AttackRange = 200.0f;
	AttackRadius = 50.0f;


}

void AGirlDoll::BeginPlay()
{
	Super::BeginPlay();
	int TestNum = 100;

	MyArea = FindClosestMonsterArea();
	MyAreaSize = MyArea->CollisionSphere->GetScaledSphereRadius();
	MyAreaLocation = MyArea->GetActorLocation(); 

	
}



void AGirlDoll::Attack_Ready()
{
	if (isAttackReady || isAttackDuring) return;

	//공격 준비 애님 몽타주

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Attack Ready"));
	isAttackReady = true;
}

void AGirlDoll::Attack_Melee()
{
	/*isAttackReady = false;
	if (isAttackDuring) return;*/
	
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Attack"));
	//OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//공격 애님 몽타주

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Attack!"));

	AttackCheck();

	/*isAttackDuring = true;*/
}

void AGirlDoll::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_EngineTraceChannel3,
		FCollisionShape::MakeSphere(AttackRadius),
		Params
	);

	
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
	if (bResult)
	{
		
		if (HitResult.GetActor())
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("HIt"));
			FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(Monster_Power, DamageEvent, GetController(), this);

			//나중에 제거 예정
			OnAttackEnd.Broadcast();

		}

	}
	
}

float AGirlDoll::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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
		//Die(getDamage, DamgaeEvent, EventInstigator, DamageCauser);
	}
	else
	{
		OnHit(getDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
	}

	return getDamage;
}

void AGirlDoll::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	if (DamageTaken > 0.0f)
	{
		
		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
	}
}

ATestMonsterArea* AGirlDoll::FindClosestMonsterArea()
{
	TArray<AActor*> OverlappingActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATestMonsterArea::StaticClass(), OverlappingActors);

	ATestMonsterArea* ClosestArea = nullptr;
	FVector GirlDollLocation = GetActorLocation();

	float MinDistance = TNumericLimits<float>::Max();

	for (AActor* Actor : OverlappingActors)
	{
		ATestMonsterArea* Area = Cast<ATestMonsterArea>(Actor);
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

void AGirlDoll::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Attack!"));

	AttackCheck();
}

