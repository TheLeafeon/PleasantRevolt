// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/MonsterBase.h"
#include "CharMoveTest/FieldMonster/FieldArea.h"
#include "CharMoveTest/FieldMonster/DoveDollAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "CharMoveTest/FieldMonster/FPSProjectile.h"
#include "DoveDoll.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class CHARMOVETEST_API ADoveDoll : public AMonsterBase
{
	GENERATED_BODY()

public:
	ADoveDoll();

	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Fire();

	void Attack();

	void AttackTimer();

	//�װ� ������� �ð�
	void DeathTimer();

	FOnAttackEndDelegate DoveDollOnAttackEnd;

	// ī�޶� ��ġ������ �ѱ� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// ������ų ������Ÿ�� Ŭ����
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	// ��ü �߻�����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* DoveDollHead;

	//MonsterArea
	AFieldArea* FindClosestMonsterArea();

	//�ǰ� �� ������
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DoveDollHitMaterial();

	//���� �� �Ҹ�
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DoveDollHitSound();

	//���� �� �Ҹ�
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DoveDollDeathSound();

	//���� �� ��ƼŬ ��� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DoveDollSpawnParticle();


	//���� Ÿ�̸�
	FTimerHandle DoveDollSpawnMoveUpHandle;

	//���� ���� z ��
	float StartZLocation;

	UPROPERTY(BlueprintReadWrite)
		FVector DoveDollHeadLocation;
	UPROPERTY(BlueprintReadWrite)
		FRotator DoveDollHeadRotation;

	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;

	UPROPERTY(BlueprintReadOnly)
	bool isDie;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

private:
	UDoveDollAnimInstance* AnimInstance;

	bool isPlayerAttackHit;
	
};
