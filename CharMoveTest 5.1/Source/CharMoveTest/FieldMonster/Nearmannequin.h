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

	//가까운 FieldArea 찾기
	AFieldArea* FindClosestMonsterArea();
	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;
	
	void Attack_Ready();
	void Attack_Melee();
	void AttackCheck();

	//Attack Task 완료 델리케이트
	FOnAttackEndDelegate NearmannequinOnAttackEnd;

	//데미지 주는 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void NearmannequinApplyDamageEvent();

	//공격 시 파티클 출력 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void NearmannequinAttackParticle();

	//피격 시 깜빡임
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void NearmannequinHitMaterial();

	//공격 모션 시간
	void AttackTimer();

	//공격 준비 시간
	void AttackReadyTimer();

	//죽고 사라지는 시간
	void DeathTimer();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);

	UPROPERTY(BlueprintReadOnly)
	bool isDie;

private:
	UNearmannequinAnimInstance* AnimInstance;

	bool isAttacking;

	//공격범위
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRange;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRadius;
};
