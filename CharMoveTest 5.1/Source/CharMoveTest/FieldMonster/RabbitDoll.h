// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/MonsterBase.h"
#include "CharMoveTest/FieldMonster/FieldArea.h"
#include "RabbitDoll.generated.h"

/**
 * 
 */
UCLASS()

class CHARMOVETEST_API ARabbitDoll : public AMonsterBase
{
	GENERATED_BODY()

public:

	ARabbitDoll();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USphereComponent* CollisionSphere;

	virtual void BeginPlay() override;

	AFieldArea* FindClosestMonsterArea();

	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;

	//액터 스폰 z 축
	float StartZLocation;

	//액터 스폰 타이머
	FTimerHandle RabbitDollSpawnMoveUpHandle;


	//virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RabbitAttackCheck();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RabbitDollKnockBack();

	void RabbitDollSpawnEffect();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* AttackRangeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector AttackRangeBoxSize;
	

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
};
