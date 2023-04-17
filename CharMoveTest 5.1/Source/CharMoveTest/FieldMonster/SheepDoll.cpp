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
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("SheepDoll_RushReady"));
	AnimInstance->PlayRush_ReadyMontage();

	FTimerHandle RushReadyTimerHandle;

	FTimerDelegate RushReadyTimerDelegate = FTimerDelegate::CreateUObject(this, &ASheepDoll::RushReadyTimer);
	GetWorldTimerManager().SetTimer(RushReadyTimerHandle, RushReadyTimerDelegate, 0.83f, false);

}

void ASheepDoll::Rush()
{

}

void ASheepDoll::Stun()
{
}

void ASheepDoll::RushReadyTimer()
{
	Rush();
}

float ASheepDoll::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void ASheepDoll::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
}

void ASheepDoll::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
}
