// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/MonsterBase.h"
#include "CharMoveTest/FieldMonster/MidBossmannequinAnimInstance.h"
#include "CharMoveTest/FieldMonster/FieldArea.h"
#include "MidBossmannequin.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FOnJumpAttackEndDelegate);

UCLASS()
class CHARMOVETEST_API AMidBossmannequin : public AMonsterBase
{
	GENERATED_BODY()
public:
	AMidBossmannequin();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	//����� FieldArea ã��
	AFieldArea* FindClosestMonsterArea();
	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* DamageRegion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector DamageRegionBoxSize;

	//Attack Task �Ϸ� ��������Ʈ
	FOnAttackEndDelegate MidBossmannequinOnAttackEnd;

	void OutRangeAttack(FVector TargetLocation);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OutRangeAttack_Rush();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OutRangeAttack_Jump(FVector TargetLocation);

	//������ �ִ� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MidBossmannequinApplyDamageEvent();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MidBossmannequinInRangeAttackParticle();


	//������ ���� �Ҹ�
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MidBossmannequinDeathSound();

	//������ ���� �Ҹ�
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MidBossmannequinHitSound();

	//�ſ￡�� �������� ���� �Ҹ�
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MidBossmannequininMirrorNearAttackSound();

	//�������� ���� �Ҹ�
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MidBossmannequinNearAttackSound();

	//�������� ���� �Ҹ�
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MidBossmannequinJumpSound();

	//�������� �ٶ� �Ҹ�
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MidBossmannequinNearAttackWindSound();

	//�ǰݽ� ���͸��� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MidBossmannequinHitmaterial();

	void OutRangeAttackEnd();


	void InRangeAttack();
	void InRangeAttackCheck();
	void InRangeAttackEnd();

	UPROPERTY(BlueprintReadWrite)
	bool isRush;

	UPROPERTY(BlueprintReadWrite)
	bool isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isMirror;

	UPROPERTY(BlueprintReadWrite)
	FVector MidPoint;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool testRightDamage;

	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	bool isDie;

	//�װ� ������� �ð�
	void DeathTimer();

	//�װ� ���� Ű ��ȯ
	UFUNCTION(BlueprintCallable)
	void GetKey(AActor* Key);
	void SpawnKey();

private:
	AActor* SaveKey;

	UMidBossmannequinAnimInstance* AnimInstance;



	bool bIsJumping;

	//���ݹ���
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRange;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRadius;
	
};
