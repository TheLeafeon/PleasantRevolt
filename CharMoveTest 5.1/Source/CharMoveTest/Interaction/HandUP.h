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
#include "CharMoveTest/Interaction/RespawnZone.h"
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

public:
	UPROPERTY(BlueprintReadWrite)
	UPrimitiveComponent* CollisionComponent;
	UPROPERTY(BlueprintReadWrite)
	UPrimitiveComponent* BlockCollisionComponent;
private:
	bool IsHandUp;
	FTimerHandle TimerHandle;

	//---IInteractionInterface---
	//플레이어와 InteractionBox콜리전과 겹쳤고 [E]키를 눌렀을 때
	virtual void InteractWithMe() override;
	//플레이어 InteractionBox콜리전과 겹쳤을 때
	virtual void ShowInteractionWidget() override;
	//플레이어 InteractionBox콜리전에서 나갔을 때
	virtual void HideInteractionWidget() override;
	//---------------------------

	void SetFalsePhysics();

	//플레이어의 애니메이션을 저장해둔 것
	UPlayerAnimInstnce* AnimInstance;

	//--HandUP을 던지듯이 내려놓을 때--
	bool IsDown;

	//Down1->->2->3
	void Down1();
	void Down2();
	void Down3();

	//BackDrop()때 실행 BackDown->Down3
	void BackDown();
	//---------------------------------

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "HandUp")
	void HandUpAni(bool value);

	//-HandUP이 강제로 떨어질 때-
	UFUNCTION(BlueprintCallable)
	void Drop();
	UFUNCTION(BlueprintCallable)
	void BackDrop();
	//---------------------------
	
	//--MirrorHandUP--
	UPROPERTY(BlueprintReadWrite)
	bool IsMirror;

	//내려놓았을 때 Mirror 안에 있을 때
	UFUNCTION(BlueprintImplementableEvent, Category = "HandUp")
	void SetMirrorHandUp();
	//Mirror 안에 있는 HandUP을 다시 집어들었을 때
	UFUNCTION(BlueprintImplementableEvent, Category = "HandUp")
	void DestroyMirrorHandUp();
	//----------------

	UPROPERTY(BlueprintReadWrite)
	UWidgetComponent* InteractionWidget;

	UPROPERTY(BlueprintReadWrite)
	bool IsOverlap;
	UPROPERTY(BlueprintReadOnly)
	FVector ExistingLocation;
};
