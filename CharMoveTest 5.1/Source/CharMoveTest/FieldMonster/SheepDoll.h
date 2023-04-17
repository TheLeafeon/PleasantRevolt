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

	//����� FieldArea ã��
	AFieldArea* FindClosestMonsterArea();
	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;

	void Rush_Ready();
	void Rush();
	void Stun();

	void RushReadyTimer();

	//������ �ִ� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SheepDollApplyDamageEvent();

	//�ǰ� �� �˹�Ǵ� �Լ� BP���� ����
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
