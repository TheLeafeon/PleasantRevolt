// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/Player/InteractionInterface.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Pawn.h"
#include "IKey.generated.h"

UCLASS()
class CHARMOVETEST_API AIKey : public APawn, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIKey();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	UPrimitiveComponent* CollisionComponent;
	UPROPERTY(BlueprintReadWrite)
	UWidgetComponent* InteractionWidget;

	UPROPERTY(BlueprintReadWrite)
	bool IsGet;

private:
	virtual void InteractWithMe() override;
	virtual void ShowInteractionWidget() override;
	virtual void HideInteractionWidget() override;
};
