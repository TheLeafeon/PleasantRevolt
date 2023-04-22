// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/MonsterBase.h"
#include "CharMoveTest/FieldMonster/FieldArea.h"
#include "Camera/CameraComponent.h"
#include "CharMoveTest/FieldMonster/FPSProjectile.h"
#include "DragonDoll.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class CHARMOVETEST_API ADragonDoll : public AMonsterBase
{
	GENERATED_BODY()
public:
	ADragonDoll();

	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void Fire();

	void Attack_Melee();

	void AttackTimer();

	FOnAttackEndDelegate DragonDollOnAttackEnd;

	// 카메라 위치에서의 총구 오프셋
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	// 스폰시킬 프로젝타일 클래스
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;

	// 구체 발사지점
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* DragonDollHead;

	//MonsterArea
	AFieldArea* FindClosestMonsterArea();

	//스폰 타이머
	FTimerHandle DragonDollSpawnMoveUpHandle;

	//액터 스폰 z 축
	float StartZLocation;

	//스폰 효과
	void DragonDollSpawnEffect();


	UPROPERTY(BlueprintReadWrite)
		FVector DragonDollHeadLocation;
	UPROPERTY(BlueprintReadWrite)
		FRotator DragonDollHeadRotation;

	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamgaeEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
};
