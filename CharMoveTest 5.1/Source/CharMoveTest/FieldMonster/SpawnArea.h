// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/FieldMonster/MonsterSpawnActor.h"
#include "CharMoveTest/FieldMonster/FieldArea.h"
#include "GameFramework/Actor.h"
#include "SpawnArea.generated.h"

UCLASS()
class CHARMOVETEST_API ASpawnArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnArea();

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, Category = "SpawnMonster")
		TArray<AMonsterSpawnActor*> AreaSpawnMonsterArray;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "FieldArea")
	AFieldArea* MyFieldArea;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "When Spawn?")
		bool isBeginOverlapMonsterSpawn;


	UFUNCTION(BlueprintCallable)
	void MonsterSpawn();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
		bool myAreaClear;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool firstIn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:


	float currentTime;

	bool bSpawn;

};
