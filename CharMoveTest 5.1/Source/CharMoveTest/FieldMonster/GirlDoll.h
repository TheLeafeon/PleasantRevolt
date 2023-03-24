// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/TestMonsterArea.h"
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


	void Attack_Ready();

	void Attack_Melee();
	FOnAttackEndDelegate OnAttackEnd;

	void AttackCheck();
	
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamgaeEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	bool isAttackDuring;
	bool isAttackReady;
	
	ATestMonsterArea* FindClosestMonsterArea();

	ATestMonsterArea* MyArea;
	FVector MyAreaLocation;
	float MyAreaSize;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRange;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackRadius;
};
