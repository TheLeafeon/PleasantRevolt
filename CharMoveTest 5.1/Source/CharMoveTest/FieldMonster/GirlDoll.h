// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/FieldArea.h"
#include "CharMoveTest/FieldMonster/MonsterBase.h"
#include "GirlDoll.generated.h"

/**
 *
 *
 */

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class CHARMOVETEST_API AGirlDoll : public AMonsterBase
{
	GENERATED_BODY()

public:
	AGirlDoll();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* AttackRangeBox;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector AttackRangeBoxSize;

	//���� �غ� �Լ�
	void Attack_Ready();

	//���� �Լ�
	void Attack_Melee();

	//Attack Task �Ϸ� ��������Ʈ
	FOnAttackEndDelegate GirlDollOnAttackEnd;

	//������ �ִ� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void GirlDollApplyDamageEvent();

	//���� �� ��ƼŬ ȿ�� ����ϴ� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void GirlDollAttackEffect();

	//�ǰ� �� �˹�Ǵ� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void GirlDollKnockBack();

	//������ �� ���� �ȹٷ� ������ �ϴ� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void GirlDollAttackSetMotion();

	//���� �� �ٽ� �����̵��� ���� ���� �ϴ� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void GirlDollAttackFinishedSetMotion();


	void GirlDollSpawnEffect();


	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamgaeEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//���� ��� �ð�
	void AttackTimer();

	//���� �غ� �ð�
	void AttackReadyTimer();

	//���� �غ� �� ����?
	UPROPERTY(BlueprintReadOnly)
		bool isAttackReady;
	//���� ��� �� ����?
	bool isAttackHit;


	AFieldArea* FindClosestMonsterArea();

	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;

	//���� ���� z ��
	float StartZLocation;

	FTimerHandle GirlDollSpawnMoveUpHandle;
};
