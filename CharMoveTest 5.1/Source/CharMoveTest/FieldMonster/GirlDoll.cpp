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

	//GirlDoll�� ���������� �ڶ󳪵��� ����
	FVector GirlDollSpawnStartLocation = GetActorLocation();
	StartZLocation = GirlDollSpawnStartLocation.Z;
	GirlDollSpawnStartLocation.Z = GirlDollSpawnStartLocation.Z - 200.0f;
	SetActorLocation(GirlDollSpawnStartLocation);

	SetActorEnableCollision(false);
	//�ڶ󳪱� Ÿ�̸�
	//FTimerHandle GirlDollSpawnMoveUpHandle;


	FTimerDelegate GirlDollSpawnMoveUpDelegate = FTimerDelegate::CreateUObject(this, &AGirlDoll::GirlDollSpawnEffect);
	GetWorldTimerManager().SetTimer(GirlDollSpawnMoveUpHandle, GirlDollSpawnMoveUpDelegate, 0.01f, true);


	int TestNum = 100;

	MyArea = FindClosestMonsterArea();
	MyAreaSize = MyArea->CollisionBox->GetScaledBoxExtent();
	MyAreaLocation = MyArea->GetActorLocation();




}


//���� �غ� �Լ�
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
//���� �Լ�
void AGirlDoll::Attack_Melee()
{
	//������ �Ǿ��ִ� actor �迭
	TArray<AActor*> OverlappingActors;
	//���� �ð� Ÿ�̸� �ڵ�
	FTimerHandle AttackTimerHandle;

	if (!isAttackHit)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Attack"));

		//������ ����
		AttackRangeBox->UpdateOverlaps();
		//�������Ǿ��ִ� ������Ʈ�� �� OverlappingActors�� �ֱ�
		AttackRangeBox->GetOverlappingActors(OverlappingActors);

		//���� ����Ʈ
		GirlDollAttackEffect();

		for (AActor* Actor : OverlappingActors)
		{
			// ���ϴ� �������� Ȯ��
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
//���� ��� �ð�
void AGirlDoll::AttackTimer()
{
	
	
	GirlDollOnAttackEnd.Broadcast();
}
//���� �غ� �ð�
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
	float TargetZ = StartZLocation; // ��ǥ ��ġ
	float Speed = 10.f; // �̵� �ӵ� (1�ʿ� 1000��ŭ �̵�)

	float DeltaZ = Speed * GetWorld()->GetDeltaSeconds();
	float NewZ = FMath::FInterpTo(CurrentZ, TargetZ, GetWorld()->GetDeltaSeconds(), Speed);
	GirlDollSpawnStartLocation.Z = NewZ;

	SetActorLocation(GirlDollSpawnStartLocation);

	if (FMath::IsNearlyEqual(NewZ, TargetZ, 0.1f)) // ��ǥ ��ġ�� �������� �� Ÿ�̸� ����
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