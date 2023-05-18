// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Teleporter.generated.h"

UCLASS()
class CHARMOVETEST_API ATeleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleporter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetOutLocation();

	UFUNCTION(BlueprintCallable, Category = "Teleport")
		void ActorTeleport(AActor* target);
private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* _RootComponent;
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* TeleportIn;
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* TeleportOut;

	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "Teleport")
		ATeleporter* TargetTeleporter;
};
