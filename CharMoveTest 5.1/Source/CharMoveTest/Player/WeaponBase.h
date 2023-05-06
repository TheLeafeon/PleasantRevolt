// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponInterface.h"
#include "NiagaraSystem.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class CHARMOVETEST_API AWeaponBase : public AActor, public IWeaponInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		virtual void Enable_Attack_Enemy() override;
	UFUNCTION(BlueprintCallable)
		virtual void Disable_Attack_Enemy() override;

protected :
	UPROPERTY(EditAnywhere, Category = "WeaponInfo")
		float PlayerAttackPower;
	UPROPERTY(EditAnywhere, Category = "WeaponInfo")
		int32 WeaponMaxCombo;
	UPROPERTY(EditAnywhere, Category = "WeaponInfo")
		float WeaponAttackNearDistance;
	UPROPERTY(EditAnywhere, Category = "WeaponInfo")
		float WeaponAttackTime;

	FString WeaponName;

	class APlayerableCharacter* MyPawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset References")
		UNiagaraSystem* AttackEnemyParticle;
private :
	UPROPERTY(EditAnywhere)
		USceneComponent* _RootComponent;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* NearWeaponMesh;
	
	bool isAttacking;

	TArray<ACharacter*> DetectedActors;
	TArray<APawn*> DetectedActors2;
	FCollisionQueryParams CollisionParams;

	UPROPERTY(EditAnywhere, Category = "Trace")
		float TraceRadius;

	float TraceLastTime;
	float TraceInterval;
	void WeaponTrace();
	void DuplicationEnemy(ACharacter* Enemy);
	void DuplicationEnemy(APawn* Enemy);

public :
	class UStaticMeshComponent* GetWeponMesh() { return NearWeaponMesh; }
	int32 GetMaxCombo() { return WeaponMaxCombo; }
	FString GetWeaponName() { return WeaponName; }
};