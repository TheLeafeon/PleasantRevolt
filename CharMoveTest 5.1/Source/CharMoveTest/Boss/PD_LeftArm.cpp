// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PD_LeftArm.h"

// Sets default values
APD_LeftArm::APD_LeftArm() : Smash_TotalTime(1.0f), IsSmash(false), Restoration_TotalTime(3.0f), Restoration(false), CurrentTime(0.0f), Alpha(0.0f), NewLocation(0), LeftArmHP(10.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APD_LeftArm::BeginPlay()
{
	Super::BeginPlay();

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

		// 액터의 위치를 업데이트합니다.
		SetActorLocation(NewLocation);

		if (GetActorLocation().Equals(TargetLocation, 0.1))
		{
			IsSmash = false;
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
			NewLocation = FMath::Lerp(TargetLocation, StartLocation, Alpha);

			// 액터의 위치를 업데이트합니다.
			SetActorLocation(NewLocation);

			if (GetActorLocation().Equals(StartLocation, 0.1))
			{
				Restoration = false;
			}
		}
	}

}

void APD_LeftArm::Smash()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Left"));

	StartLocation = GetActorLocation();
	TargetLocation = FallDecalPawn->GetFallDecalPos();
	StartTime = GetWorld()->GetTimeSeconds();

	IsSmash = true;
}

void APD_LeftArm::SmashWait()
{
	//들어올리는 애니메이션
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Left SmashWait"));
}

void APD_LeftArm::BackSmash()
{
	//다시 원상태로 돌리는 애니메이션

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Left BackSmash"));

	//다시 StartLocation로 되돌려야함
	StartTime = GetWorld()->GetTimeSeconds();

	Restoration = true;
}

void APD_LeftArm::SetFallDecalPawn(APawn* Pawn)
{
	FallDecalPawn = Cast<APD_FallDecal_Pawn>(Pawn);
}

float APD_LeftArm::TakeDamage(float Damage, FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float getDamage = Super::TakeDamage(Damage, DamgaeEvent, EventInstigator, DamageCauser);

	if (LeftArmHP <= 0.0f)
	{
		return 0.0f;
	}

	if (getDamage > 0.0f)
	{
		LeftArmHP -= getDamage;
	}

	if (LeftArmHP <= 0)
	{
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

	if (DamageTaken > 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("hit"));
		//ApplyDamageMomentum(DamageTaken, DamgaeEvent, PawnInstigator, DamageCauser);
	}
}

void APD_LeftArm::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	Destroy();
}