// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharMoveTest/Boss/Boss_BlackBoardKey.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/Public/TimerManager.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "CharMoveTest/Boss/Boss_Struct.h"

#include "BD_Boss_Character.generated.h"

UCLASS()
class CHARMOVETEST_API ABD_Boss_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABD_Boss_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBossInfo BossIfo;

private:
	FTimerHandle TimerHandle;
	FTimerHandle TimerHandle2;

	void SpawnArm();
	void GoNextLevel();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void NextLevelBP();

	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamgaeEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	UFUNCTION()
	void HPHalf();
	bool isSpawn;

	AActor* SpawnDanger; //소환한 장판 소환기

	//액터의 파티클 시스템 컴포넌트에 대한 참조 얻기
	TArray<UParticleSystemComponent*> ParticleSystemComponents;

	APlayerableCharacter* Player;


public:
	UFUNCTION(BlueprintImplementableEvent)
	void HitEffect();
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> FallObj_Spawn_Blueprint;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> Arm_Blueprint;
};
