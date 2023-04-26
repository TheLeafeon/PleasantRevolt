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


	//가까운 FieldArea 찾기
	AFieldArea* FindClosestMonsterArea();
	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;


	void Attack_Ready();
	void Attack_Melee();
	void AttackCheck();

	/*UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);*/

	//Attack Task 완료 델리케이트
	FOnAttackEndDelegate MouseDollOnAttackEnd;
	
	//데미지 주는 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MouseDollApplyDamageEvent();

	//피격 시 넉백되는 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MouseDollKnockBack();

	//공격 시 파티클 출력 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MouseDollAttackParticle();

	UFUNCTION(BlueprintCallable)
	float GetMouseDollHP();

	//공격 모션 시간
	void AttackTimer();

	//공격 준비 시간
	void AttackReadyTimer();

	//죽고 사라지는 시간
	void DeathTimer();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);

private:
	UMouseDollAnimInstance* AnimInstance;


	bool isPlayerAttackHit;


	bool isDie;
	bool isAttacking;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRange;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRadius;
};
