// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/MidBossmannequin.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "Engine/EngineTypes.h"
#include "Components/BoxComponent.h"
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

	isRush = false;
	isAttacking = false;
	isDie = false;
	bIsJumping = false;

	//오른쪽 데미지
	testRightDamage = false;

	AttackRange = 200.0f;
	AttackRadius = 50.0f;

	DamageRegionBoxSize= FVector(100.0f, 100.0f, 100.0f);
	DamageRegion= CreateDefaultSubobject<UBoxComponent>(TEXT("DamageRegionBox"));
	DamageRegion->SetBoxExtent(DamageRegionBoxSize);
	DamageRegion->SetupAttachment(GetMesh());

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

void AMidBossmannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void AMidBossmannequin::OutRangeAttack(FVector TargetLocation)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("MidBossmannequin OutRange Attack"));
	isAttacking = true;
	FVector StartLocation = GetActorLocation();

	MidPoint = (StartLocation + TargetLocation) / 2.0f;
	MidPoint.Z = MidPoint.Z + 800.0f;

	OutRangeAttack_Jump(TargetLocation);

	FTimerHandle AttackTimerHandle;
	FTimerDelegate AttackTimerDelegate = FTimerDelegate::CreateUObject(this, &AMidBossmannequin::OutRangeAttackEnd);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, 3.0, false);

}

void AMidBossmannequin::OutRangeAttackEnd()
{
	isAttacking = false;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("MidBossmannequin OutRange Attack end"));
	MidBossmannequinOnAttackEnd.Broadcast();
}

void AMidBossmannequin::InRangeAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("MidBossmannequin InRange Attack"));

	AnimInstance->PlayInRangeAttackMontage();
	MidBossmannequinNearAttackWindSound();

	FTimerHandle AttackTimerHandle;
	FTimerDelegate AttackTimerDelegate = FTimerDelegate::CreateUObject(this, &AMidBossmannequin::InRangeAttackEnd);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, Monster_Attack_Delay, false);
}

void AMidBossmannequin::InRangeAttackCheck()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("MidBossmannequin InRange Attack Hit Check"));

	MidBossmannequinInRangeAttackParticle();

	if (isMirror)
	{
		MidBossmannequininMirrorNearAttackSound();
	}
	else
	{
		MidBossmannequinNearAttackSound();
	}

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
					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("MidBossmannequin Attack Hit"));

					MidBossmannequinApplyDamageEvent();
				}
			}
		}
	}


}

void AMidBossmannequin::InRangeAttackEnd()
{
	isAttacking = false;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("MidBossmannequin InRange Attack end"));
	MidBossmannequinOnAttackEnd.Broadcast();
}

float AMidBossmannequin::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float getDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	//오버랩 되어있는 actor 배열
	TArray<AActor*> OverlappingActors;

	if (Monster_HP <= 0.0f)
	{
		return 0.0f;
	}


	//오버랩 갱신
	DamageRegion->UpdateOverlaps();
	//오버랩되어있는 컴포넌트들 다 OverlappingActors에 넣기
	DamageRegion->GetOverlappingActors(OverlappingActors);


	for (AActor* Actor : OverlappingActors)
	{
		// 원하는 액터인지 확인
		if (Actor->IsA(APlayerableCharacter::StaticClass()))
		{
			APlayerableCharacter* OtherActor = Cast<APlayerableCharacter>(Actor);
			if (OtherActor)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("MidBoss Hit"));

				MidBossmannequinHitmaterial();
				MidBossmannequinHitSound();

				if (getDamage > 0.0f)
				{
					Monster_HP -= getDamage;
				}

			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Not Hit"));
			}
		}

	}



	if (!isDie)
	{

		if (Monster_HP <= 0)
		{
			MyArea->numberOfMonstersDefeafed = MyArea->numberOfMonstersDefeafed + 1;
			//기본으로 제공해주는 Ragdoll용 CollisionProfile로 설정
			GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
			GetMesh()->SetSimulatePhysics(true);
			MidBossmannequinDeathSound();
			MidBossmannequinBGMOff();
			Die(getDamage, DamageEvent, EventInstigator, DamageCauser);
		}
		else
		{
			
			OnHit(getDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
		}
	}

	return getDamage;
}

void AMidBossmannequin::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	if (DamageTaken > 0.0f)
	{


		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
	}
}

void AMidBossmannequin::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	Monster_HP = FMath::Min(0.0f, Monster_HP);
	isDie = true;

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();

	if (isMirror)
	{
		//키 소환
		SpawnKey();
		SetDoor(false);
	}

	//문 막은거 풀림
	SetDoor(true);

	GetWorldTimerManager().ClearAllTimersForObject(this);

	FTimerHandle DeathTimerHandle;
	FTimerDelegate DeathTimerDelegate = FTimerDelegate::CreateUObject(this, &AMidBossmannequin::DeathTimer);
	GetWorldTimerManager().SetTimer(DeathTimerHandle, DeathTimerDelegate, 1.0f, false);
}

void AMidBossmannequin::DeathTimer()
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

void AMidBossmannequin::SpawnKey()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Mid"), FoundActors);

	//찾은 액터 반복
	for (AActor* Actor : FoundActors)
	{
		//특정 클래스의 액터인지 검사
		AIKey* Key = Cast<AIKey>(Actor);
		if (Key)
		{
			Key->MidKey();
		}
		ADoor* Door = Cast<ADoor>(Actor);
		if (Door)
		{
			Door->MidDown();
		}

		if (Key && Door)
		{
			break;
		}
	}
}

void AMidBossmannequin::SetDoor(bool value)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Mid2"), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		ADoor* Door = Cast<ADoor>(Actor);
		if (Door)
		{
			Door->SetIsKeyDoor(value);
			break;
		}
	}
}