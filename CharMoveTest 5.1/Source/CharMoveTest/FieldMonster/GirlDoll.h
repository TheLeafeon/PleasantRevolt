// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/MonsterBase.h"
#include "CharMoveTest/TestMonsterArea.h"
#include "CharMoveTest/FieldMonster/GirlDollAIController.h"
#include "GirlDoll.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class CHARMOVETEST_API AGirlDoll : public AMonsterBase
{
	GENERATED_BODY()
public:
	AGirlDoll();
	

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* AttackRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector AttackRangeBoxSize;

	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);


	void Attack_Ready();
	void Attack_Melee();
	void Attack_Melee_End();

	bool isReadyAttack;
	bool isDuringAttack;


	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



	


};
