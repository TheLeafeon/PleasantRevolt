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

	//가까운 FieldArea 찾기
	AFieldArea* FindClosestMonsterArea();
	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* DamageRegion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector DamageRegionBoxSize;

	//Attack Task 완료 델리케이트
	FOnAttackEndDelegate MidBossmannequinOnAttackEnd;

	void OutRangeAttack(FVector TargetLocation);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OutRangeAttack_Rush();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OutRangeAttack_Jump(FVector TargetLocation);

	//데미지 주는 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MidBossmannequinApplyDamageEvent();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MidBossmannequinInRangeAttackParticle();


	//죽을때 나는 소리
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MidBossmannequinDeathSound();

	//맞을때 나는 소리
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MidBossmannequinHitSound();

	//거울에서 근접공격 나는 소리
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MidBossmannequininMirrorNearAttackSound();

	//근접공격 나는 소리
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MidBossmannequinNearAttackSound();

	//점프공격 나는 소리
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MidBossmannequinJumpSound();

	//근접공격 바람 소리
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MidBossmannequinNearAttackWindSound();

	//피격시 머터리얼 변경
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

	//죽고 사라지는 시간
	void DeathTimer();

	//죽고 나서 키 소환
	UFUNCTION(BlueprintCallable)
	void GetKey(AActor* Key);
	void SpawnKey();

private:
	AActor* SaveKey;

	UMidBossmannequinAnimInstance* AnimInstance;



	bool bIsJumping;

	//공격범위
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRange;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		float AttackRadius;
	
};
