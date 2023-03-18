// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestDoor.h"
#include "TestDoorOpenBox.generated.h"

UCLASS()
class CHARMOVETEST_API ATestDoorOpenBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestDoorOpenBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool OpenableDoor ;

	//bool AlreadyOpenDoor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TryOpenDoor();

	UFUNCTION(BlueprintImplementableEvent)
	void OpenDoorAction();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ShowOpenDoor(UCameraComponent* CharCamera);

	UPROPERTY(BlueprintReadWrite)
	ATestDoor* LinkDoor;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FVector LinkDoorCameraLocation;
	
};
