// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MovingBasket.generated.h"

UCLASS()
class CHARMOVETEST_API AMovingBasket : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMovingBasket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "CutropeTargetTargetActor")
	class AActor* CutropeTargetActor;


	UPROPERTY(EditAnywhere, Category = "TargetActor")
	class AActor* TargetActor;

	UPROPERTY(EditAnywhere, Category = "SecondTargetActor")
	class AActor* SecondTargetActor;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	float InterpSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool firstIn;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Basket")
	UStaticMeshComponent* BasketComp;

	UFUNCTION(BlueprintCallable)
		void BasketMove();

	UFUNCTION(BlueprintImplementableEvent)
	void GoToStudioLevel();

	UFUNCTION(BlueprintImplementableEvent)
	void ShakeBasket();
private:
	FVector InitialLocation;

	FVector CutropeTargetLocation;
	FVector TargetLocation;
	FVector SecondTargetLocation;

	bool ropeBreak;
	bool basketStateNormal;
	bool firstSectionArrive;
	bool arrive;

};
