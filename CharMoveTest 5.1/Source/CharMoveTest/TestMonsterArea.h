// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestDoor.h"
#include "MonsterSpawnActor.h"
#include "TestMonsterArea.generated.h"

UCLASS()
class CHARMOVETEST_API ATestMonsterArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestMonsterArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	

	UPROPERTY(EditDefaultsOnly, Category = "MyBot")
		UStaticMeshComponent* mStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, Category = "MyBot")
		TSubclassOf<AActor>ActorToSpawn;

	UPROPERTY(EditAnywhere, Category = "MyBot")
		TArray<TSubclassOf<AActor>>myBot;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="LinkDoor")
	ATestDoor* InLinkDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LinkDoor")
	ATestDoor* OutLinkDoor;


	UPROPERTY(EditAnywhere, Category = "SpawnMonster")
		TArray<AMonsterSpawnActor*> AreaSpawnMonsterArray;

private:

	bool firstIn;

	float currentTime;

	bool bSpawn;
};
