// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/MonsterBase.h"
#include "CharMoveTest/FieldMonster/FieldArea.h"
#include "Explosionmannequin.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API AExplosionmannequin : public AMonsterBase
{
	GENERATED_BODY()
public:
	AExplosionmannequin();

	virtual void BeginPlay() override;

	//가까운 FieldArea 찾기
	AFieldArea* FindClosestMonsterArea();
	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;

	//죽고 사라지는 시간
	void DeathTimer();
	
	//터지기 전 머터리얼 변경
	void ExplosionReady();

	//터지기 전 머터리얼 변경
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ExplosionReadyMaterial();

	//터지기 전 머터리얼 변경
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ExplosionParticle();

	//데미지 주는 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ExplosionmannequinApplyDamageEvent();

	//터짐
	void Explosion();

	//터진거 hit 체크
	void ExplosionHitCheck();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);

	UPROPERTY(BlueprintReadOnly)
	bool isDie;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ExplosionRangeSphereSize;

	//폭발 반경
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* ExplosionRangeSphere;
};
