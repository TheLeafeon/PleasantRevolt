// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestDoor.generated.h"

UCLASS()
class CHARMOVETEST_API ATestDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OpenDoor();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void CloseDoor();

	/*UPROPERTY(EditAnywhere)
	AActor* DoorCamera;*/

};
