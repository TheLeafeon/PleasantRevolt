// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponInterface.h"
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
		virtual void Attack_Enemy() override;

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

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	class APlayerableCharacter* MyPawn;
private :
	UPROPERTY(EditAnywhere)
		USceneComponent* _RootComponent;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* NearWeaponMesh;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* WeaponCollision;

	bool isAttacking;
public :
	class UStaticMeshComponent* GetWeponMesh() { return NearWeaponMesh; }
	int32 GetMaxCombo() { return WeaponMaxCombo; }
	FString GetWeaponName() { return WeaponName; }
};