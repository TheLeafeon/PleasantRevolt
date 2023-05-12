// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/MidBossmannequin.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "Engine/EngineTypes.h"
#include "CharMoveTest/FieldMonster/MidBossmannequinAIController.h"
#include "CharMoveTest/FieldMonster/MidBossmannequinAnimInstance.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

AMidBossmannequin::AMidBossmannequin()
{
	AIControllerClass = AMidBossmannequinAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Monster_HP = 25.0f;
	Monster_Power = 1.0f;
	Monster_Speed = 250.0f;
	Monster_Attack_Time = 2.0f;
	Monster_Attack_Delay = 3.0f;
}

void AMidBossmannequin::BeginPlay()
{
	Super::BeginPlay();

	MyArea = FindClosestMonsterArea();
	MyAreaSize = MyArea->CollisionBox->GetScaledBoxExtent();
	MyAreaLocation = MyArea->GetActorLocation();


	AnimInstance = Cast<UMidBossmannequinAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance)
		return;

	AnimInstance->OnInRangeAttackHitCheck.AddUObject(this, &AMidBossmannequin::InRangeAttackCheck);
}

AFieldArea* AMidBossmannequin::FindClosestMonsterArea()
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

void AMidBossmannequin::OutRangeAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("MidBossmannequin OutRange Attack"));

	FTimerHandle AttackTimerHandle;
	FTimerDelegate AttackTimerDelegate = FTimerDelegate::CreateUObject(this, &AMidBossmannequin::OutRangeAttackCheck);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, Monster_Attack_Delay, false);
}

void AMidBossmannequin::OutRangeAttackCheck()
{
	//임시로 딜레이 넣고 어택 체크
	MidBossOnAttackEnd.Broadcast();
}

void AMidBossmannequin::InRangeAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("MidBossmannequin InRange Attack"));

	AnimInstance->PlayInRangeAttackMontage();

	FTimerHandle AttackTimerHandle;
	FTimerDelegate AttackTimerDelegate = FTimerDelegate::CreateUObject(this, &AMidBossmannequin::InRangeAttackCheck);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, Monster_Attack_Delay, false);
}

void AMidBossmannequin::InRangeAttackCheck()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("MidBossmannequin InRange Attack Hit Check"));
}

void AMidBossmannequin::InRangeAttackEnd()
{
	MidBossOnAttackEnd.Broadcast();
}
