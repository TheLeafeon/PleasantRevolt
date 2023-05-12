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

UCLASS()
class CHARMOVETEST_API AMidBossmannequin : public AMonsterBase
{
	GENERATED_BODY()
public:
	AMidBossmannequin();

	virtual void BeginPlay() override;


	//가까운 FieldArea 찾기
	AFieldArea* FindClosestMonsterArea();
	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;

	//Attack Task 완료 델리케이트
	FOnAttackEndDelegate MidBossOnAttackEnd;



	void OutRangeAttack();
	void OutRangeAttackCheck();

	void InRangeAttack();
	void InRangeAttackCheck();
	void InRangeAttackEnd();

private:
	UMidBossmannequinAnimInstance* AnimInstance;


	

	
};
