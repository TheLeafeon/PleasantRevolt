// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/Player/InteractionInterface.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class CHARMOVETEST_API ADoor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	UWidgetComponent* InteractionWidget;

	UPROPERTY(BlueprintReadWrite)
	bool IsDoorActive;
	UPROPERTY(BlueprintReadWrite)
	bool IsKeyDoor;

	UFUNCTION(BlueprintImplementableEvent)
	void KeyCheck();
	UFUNCTION(BlueprintImplementableEvent)
	void Down();
	UFUNCTION(BlueprintImplementableEvent)
	void MidDown();

	void SetIsKeyDoor(bool value);

private:
	virtual void InteractWithMe() override;
	virtual void ShowInteractionWidget() override;
	virtual void HideInteractionWidget() override;

	bool Complete;
};
