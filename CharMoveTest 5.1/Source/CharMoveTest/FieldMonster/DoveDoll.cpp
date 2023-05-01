// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/DoveDoll.h"
#include "CharMoveTest/CharMoveTest.h"
#include "CharMoveTest/FieldMonster/DoveDollAIController.h"
#include "DrawDebugHelpers.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ADoveDoll::ADoveDoll()
{

    AIControllerClass = ADoveDollAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    DoveDollHead = CreateDefaultSubobject<UCameraComponent>(TEXT("DoveHead"));
    DoveDollHead->SetupAttachment(GetCapsuleComponent());
    DoveDollHead->SetRelativeLocation(FVector(50.0f, 0.0f, -20.0f + BaseEyeHeight));
    DoveDollHead->bUsePawnControlRotation = true;


    Monster_HP = 2.0f;
    Monster_Power = 1.0f;
    Monster_Speed = 1.0f;
    Monster_Attack_Time = 0.0f;
    Monster_Attack_Delay = 5.0f;
    Monster_Knockback_Time = 0.0;
	isDie = false;

}

void ADoveDoll::BeginPlay()
{
    Super::BeginPlay();
    int TestNum = 100;

	AnimInstance = Cast<UDoveDollAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance)
		return;

    MyArea = FindClosestMonsterArea();
    MyAreaSize = MyArea->CollisionBox->GetScaledBoxExtent();
    MyAreaLocation = MyArea->GetActorLocation();
    
}

void ADoveDoll::Attack()
{

    if (ProjectileClass)
    {

		if (!isPlayerAttackHit)
		{
			AnimInstance->PlayAttackMontage();

			

			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Attack"));
			Fire();

		}

		isPlayerAttackHit = false;

		FTimerHandle AttackTimerHandle;
		FTimerDelegate AttackTimerDelegate = FTimerDelegate::CreateUObject(this, &ADoveDoll::AttackTimer);
		GetWorldTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, 4.0f, false);

		
    }

}

void ADoveDoll::AttackTimer()
{
    DoveDollOnAttackEnd.Broadcast();
    GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Fire"));
}

void ADoveDoll::DeathTimer()
{

	Destroy();
	
}

AFieldArea* ADoveDoll::FindClosestMonsterArea()
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

float ADoveDoll::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float getDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);


	DoveDollHitMaterial();
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

void ADoveDoll::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
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


	AnimInstance->PlayDeathMontage();
	FTimerHandle DeathTimerHandle;
	FTimerDelegate DeathTimerDelegate = FTimerDelegate::CreateUObject(this, &ADoveDoll::DeathTimer);
	GetWorldTimerManager().SetTimer(DeathTimerHandle, DeathTimerDelegate, 1.3f, false);
}

void ADoveDoll::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	if (DamageTaken > 0.0f)
	{
		isPlayerAttackHit = true;
		
		AnimInstance->PlayHitMontage();

		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
	}
}
