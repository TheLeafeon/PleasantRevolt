// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/MonsterBase.h"
#include "CharMoveTest/FieldMonster/FarmannequinAnimInstance.h"
#include "CharMoveTest/FieldMonster/FieldArea.h"
#include "Farmannequin.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);


UCLASS()
class CHARMOVETEST_API AFarmannequin : public AMonsterBase
{
	GENERATED_BODY()
public:

	AFarmannequin();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Fire();

	void Attack();
	void AttackTimer();
	void ShottingCheck();

	//�װ� ������� �ð�
	void DeathTimer();

	//���� �� ��ƼŬ ��� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void FarmannequinSpawnParticle();

	FOnAttackEndDelegate FarmannequinOnAttackEnd;

	// ������ų ������Ÿ�� Ŭ���� AFPSProjectile�� ����ü �߰� �� ����
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	//MonsterArea
	AFieldArea* FindClosestMonsterArea();
	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;

	UPROPERTY(BlueprintReadOnly)
	bool isDie;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

private:
	UFarmannequinAnimInstance* AnimInstance;


	bool isPlayerAttackHit;

};
