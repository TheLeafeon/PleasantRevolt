// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/Player/InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "CharMoveTest/FieldMonster/MonsterSpawnActor.h"
#include "PowerButton.generated.h"

UCLASS()
class CHARMOVETEST_API APowerButton : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerButton();

	/* Interaction Interface �� �Լ� ������  */
	virtual void InteractWithMe() override;
	virtual void ShowInteractionWidget() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* InteractionSampleMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool PowerOn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		USceneComponent* _RootComponent;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void PowerButtonInteraction();



};