// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharMoveTest/Player/InteractionInterface.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Engine/Public/TimerManager.h"
#include "CharMoveTest/Player/PlayerAnimInstnce.h"
#include "HandUP.generated.h"

UCLASS()
class CHARMOVETEST_API AHandUP : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandUP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	APlayerableCharacter* PlayerCharacter;

	/* Interaction Interface 속 함수 재정의  */
public:
	UPROPERTY(BlueprintReadWrite)
	UPrimitiveComponent* CollisionComponent;
private:
	bool IsHandUp;
	FTimerHandle TimerHandle;

	virtual void InteractWithMe() override;
	virtual void ShowInteractionWidget() override;
	virtual void HideInteractionWidget() override;

	void SetFalsePhysics();

	// 플레이어의 애니메이션을 저장해둔 것
	UPlayerAnimInstnce* AnimInstance;
public:
	UFUNCTION(BlueprintImplementableEvent)
	void HandUpAni(bool value);
};
