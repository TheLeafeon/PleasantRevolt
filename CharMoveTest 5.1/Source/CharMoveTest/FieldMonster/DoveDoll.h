// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/MonsterBase.h"
#include "CharMoveTest/FieldMonster/FieldArea.h"
#include "CharMoveTest/FieldMonster/DoveDollAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "CharMoveTest/FieldMonster/FPSProjectile.h"
#include "DoveDoll.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class CHARMOVETEST_API ADoveDoll : public AMonsterBase
{
	GENERATED_BODY()

public:
	ADoveDoll();

	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Fire();

	void Attack();

	void AttackTimer();

	//죽고 사라지는 시간
	void DeathTimer();

	FOnAttackEndDelegate DoveDollOnAttackEnd;

	// 카메라 위치에서의 총구 오프셋
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// 스폰시킬 프로젝타일 클래스
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	// 구체 발사지점
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* DoveDollHead;

	//MonsterArea
	AFieldArea* FindClosestMonsterArea();

	//피격 시 깜빡임
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DoveDollHitMaterial();

	//맞을 때 소리
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DoveDollHitSound();

	//죽을 때 소리
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DoveDollDeathSound();

	//스폰 시 파티클 출력 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DoveDollSpawnParticle();


	//스폰 타이머
	FTimerHandle DoveDollSpawnMoveUpHandle;

	//액터 스폰 z 축
	float StartZLocation;

	UPROPERTY(BlueprintReadWrite)
		FVector DoveDollHeadLocation;
	UPROPERTY(BlueprintReadWrite)
		FRotator DoveDollHeadRotation;

	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;

	UPROPERTY(BlueprintReadOnly)
	bool isDie;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

private:
	UDoveDollAnimInstance* AnimInstance;

	bool isPlayerAttackHit;
	
};
