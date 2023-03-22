// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/Boss_Character.h"

// Sets default values
ABoss_Character::ABoss_Character() : BossHP(20.0f), MaxBossHP(20.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint> FallObj_Spawn(TEXT("Blueprint'/Game/Boss/FallObj_Spawn.FallObj_Spawn'"));
	if (FallObj_Spawn.Object)
	{
		FallObj_Spawn_Blueprint = (UClass*)FallObj_Spawn.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void ABoss_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoss_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoss_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABoss_Character::TakeDamage(float Damage, FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float getDamage = Super::TakeDamage(Damage, DamgaeEvent, EventInstigator, DamageCauser);

	if (BossHP <= 0.0f)
	{
		return 0.0f;
	}		

	if (getDamage > 0.0f)
	{
		BossHP -= getDamage;
	}

	if (BossHP <= 0)
	{
		Die(getDamage, DamgaeEvent, EventInstigator, DamageCauser);
	}
	else
	{
		OnHit(getDamage, DamgaeEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
	}

	return getDamage;
}

void ABoss_Character::OnHit(float DamageTaken, FDamageEvent const& DamgaeEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	//�ִϸ��̼� �� ��

	if (DamageTaken > 0.0f)
	{
		//������ �ް� �ڷ� �и�
		ApplyDamageMomentum(DamageTaken, DamgaeEvent, PawnInstigator, DamageCauser);
	}
}

void ABoss_Character::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{

}

void ABoss_Character::HPHalf()
{
	//�̰� �����ϸ� �ʿ� ��ġ �Ǿ��ִ� ��������� �۵���Ű�� ������ �ұ�
	//�ƴϸ� �ֺ��� ���� ��ǥ �޾ƿͼ�... ��
	
	//�浹ü�� ���� �ٴ� ���ǰ� �´����� �����ϴ°ɷ� �ϸ� �´��� �� �浹...ó�� �ǰԲ�...

	//https://bigflash0913.tistory.com/22
	//��Į
	/*
	FVector NewSize = FVector(64.0f, 80.0f, 64.0f);
	float BoxSize = AttackRangeBox->GetScaledBoxExtent().Y;
	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * BoxSize;

	AttackRangeBox->SetBoxExtent(NewSize);
	AttackRangeBox->SetWorldLocation(NewLocation);

	//Draw RangeDecal
	NewSize.Z = 100.0f;
	FRotator NewRotator = AttackRangeBox->GetComponentRotation();
	auto RangeDecal = UGameplayStatics::SpawnDecalAtLocation(this, RangeDecalMaterial, NewSize, NewLocation, NewRotator, 0.0f);
	RangeDecal->SetFadeOut(0.0f, 1.0f);
	*/

	//�浹ü ������ ����
	if (FallObj_Spawn_Blueprint)
	{
		UWorld* world = GetWorld();
		if (world)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			FRotator rotator;
			FVector  SpawnLocation = GetActorLocation(); //�̰� ���� �� �߾ӿ� �ھƵ� �ʿ䰡 ����! �׷��� �� ���� ���� ������ �����ϴϱ�

			world->SpawnActor<AActor>(FallObj_Spawn_Blueprint, SpawnLocation, rotator, SpawnParams);
		}
	}
}