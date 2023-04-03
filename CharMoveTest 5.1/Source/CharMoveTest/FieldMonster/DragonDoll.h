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

	// �Է¿� �Լ����� ���ε��ϱ� ���� ȣ��˴ϴ�.
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION()
	void Fire();

	// ī�޶� ��ġ������ �ѱ� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	// ������ų ������Ÿ�� Ŭ����
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	// ��ü �߻�����
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* DragonDollHead;
};
