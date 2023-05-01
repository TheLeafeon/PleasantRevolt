// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharMoveTest/Interaction/DollRabbit.h"
#include "CharMoveTest/Player/InteractionInterface.h"
#include "Stand.generated.h"

UCLASS()
class CHARMOVETEST_API AStand : public AActor, public IInteractionInterface
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

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void RotationStand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnyWhere)
	bool StandMove;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
