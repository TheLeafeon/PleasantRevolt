// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/MonsterBase.h"
#include "CharMoveTest/FieldMonster/NearmannequinAnimInstance.h"
#include "CharMoveTest/FieldMonster/FieldArea.h"
#include "Nearmannequin.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class CHARMOVETEST_API ANearmannequin : public AMonsterBase
{
	GENERATED_BODY()
public:
	ANearmannequin();

	virtual void BeginPlay() override;

	//����� FieldArea ã��
	AFieldArea* FindClosestMonsterArea();
	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;
	
	void Attack_Ready();
	void Attack_Melee();
	void AttackCheck();

	//Attack Task �Ϸ� ��������Ʈ
	FOnAttackEndDelegate NearmannequinOnAttackEnd;

	//������ �ִ� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void NearmannequinApplyDamageEvent();

	//���� �� ��ƼŬ ��� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void NearmannequinAttackParticle();

	//�ǰ� �� ������
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void NearmannequinHitMaterial();

	//���� ��� �ð�
	void AttackTimer();

	//���� �غ� �ð�
	void AttackReadyTimer();

	//�װ� ������� �ð�
	void DeathTimer();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);

	UPROPERTY(BlueprintReadOnly)
	bool isDie;

private:
	UNearmannequinAnimInstance* AnimInstance;

	bool isAttacking;

	//���ݹ���
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRange;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRadius;
};
