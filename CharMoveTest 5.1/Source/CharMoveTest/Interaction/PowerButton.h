// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/Player/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "CharMoveTest/Interaction/Stand.h"
#include "Engine/DirectionalLight.h"
#include "Components/WidgetComponent.h"
#include "CharMoveTest/FieldMonster/MonsterSpawnActor.h"
#include "PowerButton.generated.h"

UCLASS()
class CHARMOVETEST_API APowerButton : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerButton();

	/* Interaction Interface 속 함수 재정의  */
	virtual void InteractWithMe() override;
	virtual void ShowInteractionWidget() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* InteractionSampleMesh;

	UPROPERTY(EditAnywhere)
	USceneComponent* _RootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AStand* LinkStand;


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PowerButtonInteraction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnyWhere)
	bool PowerOn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	UWidgetComponent* InteractionWidget;

	virtual void HideInteractionWidget() override;

};
