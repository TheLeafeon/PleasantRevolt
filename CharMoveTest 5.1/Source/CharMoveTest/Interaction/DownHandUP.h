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
#include "Components/WidgetComponent.h"
#include "Components/PrimitiveComponent.h"
#include "DownHandUP.generated.h"

UCLASS()
class CHARMOVETEST_API ADownHandUP : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADownHandUP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
		APlayerableCharacter* PlayerCharacter;

public:
	UPROPERTY(BlueprintReadWrite)
	UPrimitiveComponent* CollisionComponent;
	UPROPERTY(BlueprintReadWrite)
	UPrimitiveComponent* BlockCollisionComponent;
private:

	virtual void InteractWithMe() override;
	virtual void ShowInteractionWidget() override;
	virtual void HideInteractionWidget() override;

	void SetFalsePhysics();

	// 플레이어의 애니메이션을 저장해둔 것
	UPlayerAnimInstnce* AnimInstance;

	bool IsHandUp;
	bool IsDown;

	void Down();
	void BackDown();

	FTimerHandle TimerHandle;

	float SaveZ;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "HandUp")
	void HandUpAni(bool value);
	UFUNCTION(BlueprintCallable)
	void Drop();
	UFUNCTION(BlueprintCallable)
	void BackDrop();
	UPROPERTY(BlueprintReadWrite)
	bool IsMirror;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HandUp")
	void SetMirrorHandUp();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HandUp")
	void DestroyMirrorHandUp();

	UPROPERTY(BlueprintReadWrite)
	UWidgetComponent* InteractionWidget;
};
