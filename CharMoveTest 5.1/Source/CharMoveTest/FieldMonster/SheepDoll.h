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

	void Rush_Ready();
	void Rush();
	void Stun();

	void RushReadyTimer();

	//데미지 주는 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SheepDollApplyDamageEvent();

	//피격 시 넉백되는 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SheepDollKnockBack();


	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);

private:
	USheepDollAnimInstance* AnimInstance;

	bool isPlayerAttackHit;
	bool isDie;
	bool isAttacking;


};
