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

	//����� FieldArea ã��
	AFieldArea* FindClosestMonsterArea();
	AFieldArea* MyArea;
	FVector MyAreaLocation;
	FVector MyAreaSize;

	//�װ� ������� �ð�
	void DeathTimer();
	
	//������ �� ���͸��� ����
	void ExplosionReady();

	//������ �� ���͸��� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ExplosionReadyMaterial();

	//������ �� ���͸��� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ExplosionParticle();

	//������ �ִ� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ExplosionmannequinApplyDamageEvent();

	//����
	void Explosion();

	//������ hit üũ
	void ExplosionHitCheck();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);

	UPROPERTY(BlueprintReadOnly)
	bool isDie;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ExplosionRangeSphereSize;

	//���� �ݰ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* ExplosionRangeSphere;
};
