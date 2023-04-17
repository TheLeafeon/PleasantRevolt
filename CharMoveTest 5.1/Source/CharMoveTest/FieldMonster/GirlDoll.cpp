// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/GirlDoll.h"
#include "CharMoveTest/CharMoveTest.h"
#include "Components/BoxComponent.h"
#include "CharMoveTest/FieldMonster/GirlDollAIController.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
//#include "Engine.h"


AGirlDoll::AGirlDoll()
{

	AIControllerClass = AGirlDollAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


	Monster_HP = 3.0f;
	Monster_Power = 1.0f;
	Monster_Speed = 2.0f;
	Monster_Attack_Time = 0.3f;
	Monster_Attack_Delay = 0.5f;
	Monster_Knockback_Time = 0.5;
	AttackRangeBoxSize = FVector(100.0f, 100.0f, 100.0f);

	AttackRangeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackRange"));

	AttackRangeBox->SetBoxExtent(AttackRangeBoxSize);
	AttackRangeBox->SetupAttachment(GetMesh());

	isAttackHit = false;
	isAttackReady = false;


	AttackRangeBox->OnComponentBeginOverlap.AddDynamic(this, &AGirlDoll::OnOverlapBegin);

}

void AGirlDoll::BeginPlay()
{
	Super::BeginPlay();

	//GirlDoll이 땅에서부터 자라나듯이 스폰
	FVector GirlDollSpawnStartLocation = GetActorLocation();
	StartZLocation = GirlDollSpawnStartLocation.Z;
	GirlDollSpawnStartLocation.Z = GirlDollSpawnStartLocation.Z - 200.0f;
	SetActorLocation(GirlDollSpawnStartLocation);

	SetActorEnableCollision(false);
	//자라나기 타이머
	//FTimerHandle GirlDollSpawnMoveUpHandle;


	FTimerDelegate GirlDollSpawnMoveUpDelegate = FTimerDelegate::CreateUObject(this, &AGirlDoll::GirlDollSpawnEffect);
	GetWorldTimerManager().SetTimer(GirlDollSpawnMoveUpHandle, GirlDollSpawnMoveUpDelegate, 0.01f, true);


	int TestNum = 100;

	MyArea = FindClosestMonsterArea();
	MyAreaSize = MyArea->CollisionBox->GetScaledBoxExtent();
	MyAreaLocation = MyArea->GetActorLocation();




}


//공격 준비 함수
void AGirlDoll::Attack_Ready()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Attack Ready"));
	isAttackReady = true;
	isAttackHit = false;
	GirlDollAttackSetMotion();

	FTimerHandle AttackReadyTimerHandle;

	FTimerDelegate AttackReadyTimerDelegate = FTimerDelegate::CreateUObject(this, &AGirlDoll::AttackReadyTimer);
	GetWorldTimerManager().SetTimer(AttackReadyTimerHandle, AttackReadyTimerDelegate, Monster_Attack_Time, false);

}
//공격 함수
void AGirlDoll::Attack_Melee()
{
	//오버랩 되어있는 actor 배열
	TArray<AActor*> OverlappingActors;
	//공격 시간 타이머 핸들
	FTimerHandle AttackTimerHandle;

	if (!isAttackHit)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Attack"));

		//오버랩 갱신
		AttackRangeBox->UpdateOverlaps();
		//오버랩되어있는 컴포넌트들 다 OverlappingActors에 넣기
		AttackRangeBox->GetOverlappingActors(OverlappingActors);

		//공격 이펙트
		GirlDollAttackEffect();

		for (AActor* Actor : OverlappingActors)
		{
			// 원하는 액터인지 확인
			if (Actor->IsA(APlayerableCharacter::StaticClass()))
			{
				APlayerableCharacter* OtherActor = Cast<APlayerableCharacter>(Actor);
				if (OtherActor)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("GirDoll Attack Hit"));
					//isAttackHit = true;
					GirlDollApplyDamageEvent();
				}
				
			}

		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("GirDoll Attack Miss"));
	}
	isAttackReady = false;
	GirlDollAttackFinishedSetMotion();
	FTimerDelegate AttackTimerDelegate = FTimerDelegate::CreateUObject(this, &AGirlDoll::AttackTimer);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, Monster_Attack_Delay, false);

}
//공격 모션 시간
void AGirlDoll::AttackTimer()
{
	
	
	GirlDollOnAttackEnd.Broadcast();
}
//공격 준비 시간
void AGirlDoll::AttackReadyTimer()
{
	Attack_Melee();
}

void AGirlDoll::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AGirlDoll::GirlDollSpawnEffect()
{
	FVector GirlDollSpawnStartLocation = GetActorLocation();
	float CurrentZ = GirlDollSpawnStartLocation.Z;
	float TargetZ = StartZLocation; // 목표 위치
	float Speed = 10.f; // 이동 속도 (1초에 1000만큼 이동)

	float DeltaZ = Speed * GetWorld()->GetDeltaSeconds();
	float NewZ = FMath::FInterpTo(CurrentZ, TargetZ, GetWorld()->GetDeltaSeconds(), Speed);
	GirlDollSpawnStartLocation.Z = NewZ;

	SetActorLocation(GirlDollSpawnStartLocation);

	if (FMath::IsNearlyEqual(NewZ, TargetZ, 0.1f)) // 목표 위치에 도달했을 때 타이머 종료
	{
		SetActorEnableCollision(true);
		GetWorld()->GetTimerManager().ClearTimer(GirlDollSpawnMoveUpHandle);
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
		MyArea->numberOfMonstersDefeafed = MyArea->numberOfMonstersDefeafed + 1;
		Destroy();
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
		isAttackHit = true;
		//GirlDollOnAttackEnd.Broadcast();

		GirlDollKnockBack();

		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);


	}
}

AFieldArea* AGirlDoll::FindClosestMonsterArea()
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