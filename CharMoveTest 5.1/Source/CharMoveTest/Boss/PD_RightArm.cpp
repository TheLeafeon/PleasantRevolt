// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/PD_RightArm.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APD_RightArm::APD_RightArm() : Smash_TotalTime(1.0f), IsSmash(false), Restoration_TotalTime(3.0f), Restoration(false), CurrentTime(0.0f), Alpha(0.0f), NewLocation(0), RightArmHP(10.0f), IsAttack(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APD_RightArm::BeginPlay()
{
	Super::BeginPlay();

	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APD_RightArm::OnOverlapBegin);
}

// Called every frame
void APD_RightArm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsSmash)
	{
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Player->GetActorLocation());
		SetActorRotation(LookAtRotation + FRotator(-50.0f, 50.0f, -50.0f));

		// 현재 시간을 계산합니다.
		CurrentTime = GetWorld()->GetTimeSeconds() - StartTime;

		// 보간 계산을 위한 알파 값을 계산합니다.
		Alpha = FMath::Clamp(CurrentTime / Smash_TotalTime, 0.0f, 1.0f);

		// 보간된 위치를 계산합니다.
		NewLocation = FMath::Lerp(StartLocation, TargetLocation, Alpha);
		//NewRotator = FMath::Lerp(StartRotator, FRotator(0.0f, 90.0f, 0.0f), Alpha);

		// 액터의 위치를 업데이트합니다.
		SetActorLocation(NewLocation);
		//SetActorRotation(NewRotator);

		if (GetActorLocation().Equals(TargetLocation, 0.1))
		{
			IsSmash = false;
			IsAttack = true;
			r = GetActorRotation();
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
			NewRotator = FMath::Lerp(r, StartRotator, Alpha);

			// 보간된 위치를 계산합니다.
			NewLocation = FMath::Lerp(TargetLocation, StartLocation, Alpha);

			// 액터의 위치를 업데이트합니다.
			SetActorLocation(NewLocation);
			SetActorRotation(NewRotator);

			if (GetActorLocation().Equals(StartLocation, 0.1))
			{
				Restoration = false;
				CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
				SetWaitAni(false);
				SetAttackAni(false);
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
	StartRotator = GetActorRotation();

	IsSmash = true;

	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SetAttackAni(true);
}

void APD_RightArm::SmashWait()
{
	//들어올리는 애니메이션
	SetWaitAni(true);
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

float APD_RightArm::TakeDamage(float Damage, FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float getDamage = Super::TakeDamage(Damage, DamgaeEvent, EventInstigator, DamageCauser);

	if (RightArmHP <= 0.0f)
	{
		return 0.0f;
	}

	if (getDamage > 0.0f)
	{
		RightArmHP -= getDamage;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("hit"));
	}

	if (RightArmHP <= 0)
	{
		Die(getDamage, DamgaeEvent, EventInstigator, DamageCauser);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Die"));
	}
	else
	{
		OnHit(getDamage, DamgaeEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
	}

	return getDamage;
}

void APD_RightArm::OnHit(float DamageTaken, FDamageEvent const& DamgaeEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	//애니메이션 들어갈 곳

	if (DamageTaken > 0.0f)
	{
		//ApplyDamageMomentum(DamageTaken, DamgaeEvent, PawnInstigator, DamageCauser);
	}
}

void APD_RightArm::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	Destroy();
}

void APD_RightArm::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Attack"));
	if (OtherActor == Player)
	{
		if (IsSmash && IsAttack)
		{
			UGameplayStatics::ApplyDamage(Player, 1, NULL, this, UDamageType::StaticClass());
			IsAttack = false;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Attack"));
		}
	}
}