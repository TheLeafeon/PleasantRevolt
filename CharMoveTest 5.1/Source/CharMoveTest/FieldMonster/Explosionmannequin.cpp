// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/Explosionmannequin.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "CharMoveTest/FieldMonster/ExplosionmannequinAIController.h"
#include "Engine/EngineTypes.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

AExplosionmannequin::AExplosionmannequin()
{
	AIControllerClass = AExplosionmannequinAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Monster_HP = 15.0f;
	Monster_Power = 1.0f;
	Monster_Speed = 150.0f;

	ExplosionRangeSphereSize = 300.0f;

	ExplosionRangeSphere= CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionRange"));
	ExplosionRangeSphere->SetSphereRadius(ExplosionRangeSphereSize);
	ExplosionRangeSphere->SetupAttachment(RootComponent);
	isDie = false;
}

void AExplosionmannequin::BeginPlay()
{
	Super::BeginPlay();

	MyArea = FindClosestMonsterArea();
	MyAreaSize = MyArea->CollisionBox->GetScaledBoxExtent();
	MyAreaLocation = MyArea->GetActorLocation();

}

AFieldArea* AExplosionmannequin::FindClosestMonsterArea()
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

void AExplosionmannequin::DeathTimer()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("DeathTimer"));

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



	Destroy();
}

void AExplosionmannequin::ExplosionReady()
{
	ExplosionReadyMaterial();

	FTimerHandle ExplosionTimerHandle;
	FTimerDelegate ExplosionTimerDelegate = FTimerDelegate::CreateUObject(this, &AExplosionmannequin::Explosion);
	GetWorldTimerManager().SetTimer(ExplosionTimerHandle, ExplosionTimerDelegate, 3.0f, false);


}

void AExplosionmannequin::Explosion()
{
	TArray<AActor*> OverlappingActors;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Explosion"));
	ExplosionParticle();

	ExplosionRangeSphere->UpdateOverlaps();

	ExplosionRangeSphere->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		// 원하는 액터인지 확인
		if (Actor->IsA(APlayerableCharacter::StaticClass()))
		{
			APlayerableCharacter* OtherActor = Cast<APlayerableCharacter>(Actor);
			if (OtherActor)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Explosion Hit"));
				ExplosionmannequinApplyDamageEvent();
			}
			
		}
	}

	FTimerHandle DeathTimerHandle;
	FTimerDelegate DeathTimerDelegate = FTimerDelegate::CreateUObject(this, &AExplosionmannequin::DeathTimer);
	GetWorldTimerManager().SetTimer(DeathTimerHandle, DeathTimerDelegate, 1.0f, false);
}

void AExplosionmannequin::ExplosionHitCheck()
{
}

float AExplosionmannequin::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

void AExplosionmannequin::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	if (DamageTaken > 0.0f)
	{

		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
	}
}

void AExplosionmannequin::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	Monster_HP = FMath::Min(0.0f, Monster_HP);
	isDie = true;

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();

	GetWorldTimerManager().ClearAllTimersForObject(this);
	ExplosionReady();

	
}
