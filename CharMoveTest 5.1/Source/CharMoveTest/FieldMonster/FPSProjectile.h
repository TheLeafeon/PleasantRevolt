// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FPSProjectile.generated.h"

UCLASS()
class CHARMOVETEST_API AFPSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	UFUNCTION(BlueprintCallable)
	void FarmannequinProjectile();


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 구체 콜리전 컴포넌트입니다.
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly, Category = Projectile)
		USphereComponent* CollisionComponent;

	// 프로젝타일 무브먼트 컴포넌트
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite ,Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;

	//충돌 시
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void FarmannequinProjectileHitSound();

	// 발사체의 속도를 발사 방향으로 초기화시킵니다.
	void FireInDirection(const FVector& ShootDirection);


	// 프로젝타일이 무언가에 맞으면 호출되는 함수입니다.
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	

	void OnCollision(const FHitResult& HitResult);

	UPROPERTY(BlueprintReadOnly)
		float Fire_Power;
};
