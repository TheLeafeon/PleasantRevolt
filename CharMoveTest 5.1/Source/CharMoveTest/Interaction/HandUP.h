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
	//�÷��̾�� InteractionBox�ݸ����� ���ư� [E]Ű�� ������ ��
	virtual void InteractWithMe() override;
	//�÷��̾� InteractionBox�ݸ����� ������ ��
	virtual void ShowInteractionWidget() override;
	//�÷��̾� InteractionBox�ݸ������� ������ ��
	virtual void HideInteractionWidget() override;
	//---------------------------

	void SetFalsePhysics();

	//�÷��̾��� �ִϸ��̼��� �����ص� ��
	UPlayerAnimInstnce* AnimInstance;

	//--HandUP�� �������� �������� ��--
	bool IsDown;

	//Down1->->2->3
	void Down1();
	void Down2();
	void Down3();

	//BackDrop()�� ���� BackDown->Down3
	void BackDown();
	//---------------------------------

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "HandUp")
	void HandUpAni(bool value);

	//-HandUP�� ������ ������ ��-
	UFUNCTION(BlueprintCallable)
	void Drop();
	UFUNCTION(BlueprintCallable)
	void BackDrop();
	//---------------------------
	
	//--MirrorHandUP--
	UPROPERTY(BlueprintReadWrite)
	bool IsMirror;

	//���������� �� Mirror �ȿ� ���� ��
	UFUNCTION(BlueprintImplementableEvent, Category = "HandUp")
	void SetMirrorHandUp();
	//Mirror �ȿ� �ִ� HandUP�� �ٽ� �������� ��
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
