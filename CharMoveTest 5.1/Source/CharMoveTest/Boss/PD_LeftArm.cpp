// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PD_LeftArm.h"

// Sets default values
APD_LeftArm::APD_LeftArm() : Smash_TotalTime(0.5f), IsSmash(false), Restoration_TotalTime(3.0f), Restoration(false), CurrentTime(0.0f), Alpha(0.0f), NewLocation(0), LeftArmHP(10.0f), IsAttack(false), IsHitOk(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APD_LeftArm::BeginPlay()
{
	Super::BeginPlay();

	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	//CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APD_LeftArm::OnOverlapBegin);
}

// Called every frame
void APD_LeftArm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsSmash)
	{
		// 현재 시간을 계산합니다.
		CurrentTime = GetWorld()->GetTimeSeconds() - StartTime;

		// 보간 계산을 위한 알파 값을 계산합니다.
		Alpha = FMath::Clamp(CurrentTime / Smash_TotalTime, 0.0f, 1.0f);

		// 보간된 위치를 계산합니다.
		NewLocation = FMath::Lerp(StartLocation, TargetLocation, Alpha);
		//NewRotator = FMath::Lerp(StartRotator, FRotator(0.0f, 90.0f, 105.0f), Alpha);

		// 액터의 위치를 업데이트합니다.
		SetActorLocation(NewLocation);
		//SetActorRotation(NewRotator);

		if (GetActorLocation().Equals(TargetLocation, 0.1))
		{
			IsSmash = false;
			IsAttack = true;
		}
	}
	else
	{
		if (Restoration)
		{
			// 현재 시간을 계산합니다.
			CurrentTime = GetWorld()->GetTimeSeconds() - StartTime;

			// 보간 계산을 위한 알파 값을 계산합니다.
			Alpha = FMath::Clamp(CurrentTime / Restoration_TotalTime, 0.0f, 1.0f);

			// 보간된 위치를 계산합니다.
			NewLocation = FMath::Lerp(TargetLocation, EndLocation, Alpha);
			//NewRotator = FMath::Lerp(FRotator(0.0f, 90.0f, 105.0f), StartRotator, Alpha);

			// 액터의 위치를 업데이트합니다.
			SetActorLocation(NewLocation);
			//SetActorRotation(NewRotator);

			if (GetActorLocation().Equals(EndLocation, 0.1))
			{
				Restoration = false;
				CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
				IsHitOk = false;
			}
		}
	}

}

void APD_LeftArm::Smash()
{
	IsHitOk = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Left"));

	StartLocation = GetActorLocation() + FVector(0.0f, 0.0f, 1600.0f);
	EndLocation = GetActorLocation();
	TargetLocation = FallDecalPawn->GetFallDecalPos() + FVector(1050.0f, 550.0f, 620.0f);
	StartTime = GetWorld()->GetTimeSeconds();
	//StartRotator = GetActorRotation();

	IsSmash = true;
	
	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SetAttackAni(true);
}

void APD_LeftArm::SmashWait()
{
	//들어올리는 애니메이션
	SetWaitAni(true);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Left SmashWait"));
}

void APD_LeftArm::BackSmash()
{
	//다시 원상태로 돌리는 애니메이션

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Left BackSmash"));

	//다시 StartLocation로 되돌려야함
	StartTime = GetWorld()->GetTimeSeconds();

	Restoration = true;
	SetWaitAni(false);
	SetAttackAni(false);
}

void APD_LeftArm::SetFallDecalPawn(APawn* Pawn)
{
	FallDecalPawn = Cast<APD_FallDecal_Pawn>(Pawn);
}

float APD_LeftArm::TakeDamage(float Damage, FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float getDamage = Super::TakeDamage(Damage, DamgaeEvent, EventInstigator, DamageCauser);

	if (!IsHitOk)
	{
		return 0.0f;
	}

	if (LeftArmHP <= 0.0f)
	{
		return 0.0f;
	}

	if (getDamage > 0.0f)
	{
		LeftArmHP -= getDamage;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("hit"));
	}

	if (LeftArmHP <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Die"));
		Die(getDamage, DamgaeEvent, EventInstigator, DamageCauser);
	}
	else
	{
		OnHit(getDamage, DamgaeEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
	}

	return getDamage;
}

void APD_LeftArm::OnHit(float DamageTaken, FDamageEvent const& DamgaeEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	//애니메이션 들어갈 곳
	HitEffect();
	if (DamageTaken > 0.0f)
	{
		
		//ApplyDamageMomentum(DamageTaken, DamgaeEvent, PawnInstigator, DamageCauser);
	}
}

void APD_LeftArm::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	GetComponents<UParticleSystemComponent>(ParticleSystemComponents);
	for (UParticleSystemComponent* ParticleSystemComponent : ParticleSystemComponents)
	{
		ParticleSystemComponent->DestroyComponent();
	}

	Destroy();
}
