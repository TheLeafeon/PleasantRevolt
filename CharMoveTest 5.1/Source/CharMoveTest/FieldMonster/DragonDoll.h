// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/MonsterBase.h"
#include "Camera/CameraComponent.h"
#include "CharMoveTest/FieldMonster/FPSProjectile.h"
#include "DragonDoll.generated.h"

/**
 * 
 */
UCLASS()
class CHARMOVETEST_API ADragonDoll : public AMonsterBase
{
	GENERATED_BODY()
public:
	ADragonDoll();


	void Attack_Ready();
	void Attack_Melee();
	void Attack_Melee_End();

	bool isReadyAttack;
	bool isDuringAttack;

	// 입력에 함수성을 바인딩하기 위해 호출됩니다.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION()
	void Fire();

	// 카메라 위치에서의 총구 오프셋
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	// 스폰시킬 프로젝타일 클래스
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	// 구체 발사지점
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* DragonDollHead;
};
