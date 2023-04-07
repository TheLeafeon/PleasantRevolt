// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PD_RightArm.h"

// Sets default values
APD_RightArm::APD_RightArm() : Smash_TotalTime(1.0f), IsSmash(false), Restoration_TotalTime(3.0f), Restoration(false), CurrentTime(0.0f), Alpha(0.0f), NewLocation(0)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APD_RightArm::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APD_RightArm::Tick(float DeltaTime)
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
		GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Red, TEXT("else"));
		if (Restoration == true)
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

void APD_RightArm::Smash()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Right"));

	StartLocation = GetActorLocation();
	TargetLocation = FallDecalPawn->GetFallDecalPos();
	StartTime = GetWorld()->GetTimeSeconds();

	IsSmash = true;
}

void APD_RightArm::SmashWait()
{
	//들어올리는 애니메이션
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Right SmashWait"));
}

void APD_RightArm::BackSmash()
{
	//다시 원상태로 돌리는 애니메이션

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Right BackSmash"));

	//다시 StartLocation로 되돌려야함
	StartTime = GetWorld()->GetTimeSeconds();

	Restoration = true;
}

void APD_RightArm::SetFallDecalPawn(APawn* Pawn)
{
	FallDecalPawn = Cast<APD_FallDecal_Pawn>(Pawn);
}