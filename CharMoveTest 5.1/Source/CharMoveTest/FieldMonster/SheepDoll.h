// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/MonsterBase.h"
#include "CharMoveTest/FieldMonster/SheepDollAnimInstance.h"
#include "CharMoveTest/FieldMonster/FieldArea.h"
#include "SheepDoll.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackReadyEndDelegate);
DECLARE_MULTICAST_DELEGATE(FStunEndDelegate);

UCLASS()
class CHARMOVETEST_API ASheepDoll : public AMonsterBase
{
	GENERATED_BODY()
public:
	ASheepDoll();

	virtual void BeginPlay() override;

	//����� FieldArea ã��
	AFieldArea* FindClosestMonsterArea();
	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* AttackRangeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector AttackRangeBoxSize;

	void Rush_Ready();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Rush();

	UFUNCTION(BlueprintCallable)
	void Stun();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void IsStunEnd();
	
	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly)
	bool isAttacking;

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly)
	bool isStun;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	bool isPlayerAttackHit;



	void RushReadyTimer();
	void StunTimer();


	//AttackReady Task �Ϸ� ��������Ʈ
	FOnAttackEndDelegate SheepDollOnAttackReadyEnd;

	//Attack Task �Ϸ� ��������Ʈ
	FOnAttackReadyEndDelegate SheepDollOnAttackEnd;

	//Stun Task �Ϸ� ��������Ʈ
	FStunEndDelegate SheepDollStunEnd;

	//������ �ִ� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SheepDollApplyDamageEvent();

	//�ǰ� �� �˹�Ǵ� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SheepDollKnockBack();

	//�׾����� �� �ָ� �˹�Ǵ� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SheepDollDeathKnockBack();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SheepDollRushParticle();

	//�ǰ� �� ������
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SheepDollHitMaterial();

	//�װ� ������� �ð�
	void DeathTimer();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);


	USheepDollAnimInstance* AnimInstance;

	//������ ��ƼŬ �ý��� ������Ʈ�� ���� ���� ���
	TArray<UParticleSystemComponent*> ParticleSystemComponents;

	

private:

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Die, Meta = (AllowPrivateAccess = true))
	bool isDie;



};
