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

	//공격 준비 함수
	void Attack_Ready();

	//공격 함수
	void Attack_Melee();

	//Attack Task 완료 델리케이트
	FOnAttackEndDelegate GirlDollOnAttackEnd;

	//데미지 주는 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void GirlDollApplyDamageEvent();

	//공격 시 파티클 효과 출력하는 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void GirlDollAttackEffect();

	//피격 시 넉백되는 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void GirlDollKnockBack();

	//공격할 때 인형 똑바로 서도록 하는 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void GirlDollAttackSetMotion();

	//공격 후 다시 움직이도록 변수 변경 하는 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void GirlDollAttackFinishedSetMotion();


	void GirlDollSpawnEffect();


	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamgaeEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//공격 모션 시간
	void AttackTimer();

	//공격 준비 시간
	void AttackReadyTimer();

	//공격 준비 중 인지?
	UPROPERTY(BlueprintReadOnly)
		bool isAttackReady;
	//공격 모션 중 인지?
	bool isAttackHit;


	AFieldArea* FindClosestMonsterArea();

	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;

	//액터 스폰 z 축
	float StartZLocation;

	FTimerHandle GirlDollSpawnMoveUpHandle;
};
