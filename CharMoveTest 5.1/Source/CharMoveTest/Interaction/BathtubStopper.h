// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/Player/InteractionInterface.h"
#include "Components/WidgetComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/Actor.h"
#include "BathtubStopper.generated.h"

UCLASS()
class CHARMOVETEST_API ABathtubStopper : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	ABathtubStopper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private :
	virtual void InteractWithMe() override;
	virtual void ShowInteractionWidget() override;
	virtual void HideInteractionWidget() override;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* _RootComponent;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BathtubStopperMesh;

	UPROPERTY(EditAnywhere)
		UWidgetComponent* InteractionWidget;

	UPROPERTY(EditAnywhere, Category = "Target")
		AActor* Target;
	UPROPERTY(EditAnywhere, Category = "Launch")
		float LaunchForce;

	bool isLaunch;
public :
	UFUNCTION(BlueprintCallable, Category = "Launch")
		void LaunchActor();
	UFUNCTION(BlueprintCallable, Category = "Target")
		void DeleteTarget();
};
