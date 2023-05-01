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

	//가까운 FieldArea 찾기
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


	//AttackReady Task 완료 델리케이트
	FOnAttackEndDelegate SheepDollOnAttackReadyEnd;

	//Attack Task 완료 델리케이트
	FOnAttackReadyEndDelegate SheepDollOnAttackEnd;

	//Stun Task 완료 델리케이트
	FStunEndDelegate SheepDollStunEnd;

	//데미지 주는 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SheepDollApplyDamageEvent();

	//피격 시 넉백되는 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SheepDollKnockBack();

	//죽었을때 더 멀리 넉백되는 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SheepDollDeathKnockBack();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SheepDollRushParticle();

	//피격 시 깜빡임
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SheepDollHitMaterial();

	//죽고 사라지는 시간
	void DeathTimer();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);


	USheepDollAnimInstance* AnimInstance;

	//액터의 파티클 시스템 컴포넌트에 대한 참조 얻기
	TArray<UParticleSystemComponent*> ParticleSystemComponents;

	

private:

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Die, Meta = (AllowPrivateAccess = true))
	bool isDie;



};
