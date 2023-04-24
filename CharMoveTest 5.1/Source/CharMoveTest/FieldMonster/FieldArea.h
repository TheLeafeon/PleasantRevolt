// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharMoveTest/FieldMonster/MonsterSpawnActor.h"
#include "FieldArea.generated.h"

UCLASS()
class CHARMOVETEST_API AFieldArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFieldArea();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, Category = "SpawnMonster")
		TArray<AMonsterSpawnActor*> AreaSpawnMonsterArray;

	UPROPERTY(EditAnywhere, Category = "SpawnMonsterWave2")
		TArray<AMonsterSpawnActor*> AreaSpawnMonsterArrayWave2;

	UPROPERTY(EditAnywhere, Category = "SpawnMonsterWave3")
		TArray<AMonsterSpawnActor*> AreaSpawnMonsterArrayWave3;


	UFUNCTION(BlueprintCallable)
		void Wave2Spawn();

	UFUNCTION(BlueprintCallable)
		void Wave3Spawn();


	//처치된 몬스터 수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int numberOfMonstersDefeafed;

	//Wave2가 시작되었는지
	bool Wave2Start;

	//Wave3가 시작되었는지
	bool Wave3Start;


	//Area의 Wave 수 설정
	UPROPERTY(EditAnywhere)
		int thisAreaWaveNumber;

private:

	bool firstIn;

	float currentTime;

	bool bSpawn;

};
