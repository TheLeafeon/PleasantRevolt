// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/MonsterBase.h"
#include "CharMoveTest/FieldMonster/FieldArea.h"
#include "Camera/CameraComponent.h"
#include "CharMoveTest/FieldMonster/FPSProjectile.h"
#include "DragonDoll.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class CHARMOVETEST_API ADragonDoll : public AMonsterBase
{
	GENERATED_BODY()
public:
	ADragonDoll();

	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void Fire();

	void Attack_Melee();

	void AttackTimer();

	FOnAttackEndDelegate DragonDollOnAttackEnd;

	// ī�޶� ��ġ������ �ѱ� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	// ������ų ������Ÿ�� Ŭ����
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;

	// ��ü �߻�����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* DragonDollHead;

	//MonsterArea
	AFieldArea* FindClosestMonsterArea();

	//���� Ÿ�̸�
	FTimerHandle DragonDollSpawnMoveUpHandle;

	//���� ���� z ��
	float StartZLocation;

	//���� ȿ��
	void DragonDollSpawnEffect();


	UPROPERTY(BlueprintReadWrite)
		FVector DragonDollHeadLocation;
	UPROPERTY(BlueprintReadWrite)
		FRotator DragonDollHeadRotation;

	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamgaeEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
};
