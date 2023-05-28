// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/MonsterBase.h"
#include "CharMoveTest/FieldMonster/MouseDollAnimInstance.h"
#include "CharMoveTest/FieldMonster/FieldArea.h"
#include "MouseDoll.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class CHARMOVETEST_API AMouseDoll : public AMonsterBase
{
	GENERATED_BODY()
public:
	AMouseDoll();

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;


	//����� FieldArea ã��
	AFieldArea* FindClosestMonsterArea();
	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;


	void Attack_Ready();
	void Attack_Melee();
	void AttackCheck();

	//Attack Task �Ϸ� ��������Ʈ
	FOnAttackEndDelegate MouseDollOnAttackEnd;
	
	//������ �ִ� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MouseDollApplyDamageEvent();

	//�ǰ� �� �˹�Ǵ� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MouseDollKnockBack();

	//���� �� ��ƼŬ ��� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MouseDollAttackParticle();

	//���� �� ��ƼŬ ��� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MouseDollSpawnParticle();

	//�׾����� �� �ָ� �˹�Ǵ� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MouseDollDeathKnockBack();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MouseDollHitSound();

	//�ǰ� �� ������
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MouseDollHitMaterial();

	//�÷��̾� ���󰡱�
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MouseDollMoveToTarget();

	UFUNCTION(BlueprintCallable)
	float GetMouseDollHP();

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
	UMouseDollAnimInstance* AnimInstance;


	bool isPlayerAttackHit;
	
	bool isAttacking;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRange;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRadius;
};
