// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharMoveTest/Player/InteractionInterface.h"
#include "CharMoveTest/Interaction/BigDoll.h"
#include "Stand.generated.h"

UCLASS()
class CHARMOVETEST_API AStand : public AActor , public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStand();

	/* Interaction Interface 속 함수 재정의  */
	virtual void InteractWithMe() override;
	virtual void ShowInteractionWidget() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* InteractionSampleMesh;

	UPROPERTY(EditAnywhere)
		USceneComponent* _RootComponent;

	UPROPERTY(EditAnywhere, Category = "DuckDoll")
	class ABigDoll* DuckDoll;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StandRotation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool StandMove;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
