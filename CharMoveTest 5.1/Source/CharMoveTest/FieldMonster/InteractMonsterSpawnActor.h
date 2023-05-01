// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharMoveTest/Player/InteractionInterface.h"
#include "Components/WidgetComponent.h"
#include "CharMoveTest/FieldMonster/MonsterSpawnActor.h"
#include "CharMoveTest/FieldMonster/FieldArea.h"
#include "GameFramework/Actor.h"
#include "InteractMonsterSpawnActor.generated.h"

UCLASS()
class CHARMOVETEST_API AInteractMonsterSpawnActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractMonsterSpawnActor();

	/* Interaction Interface �� �Լ� ������  */
	virtual void InteractWithMe() override;
	virtual void ShowInteractionWidget() override;
	virtual void HideInteractionWidget() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "SpawnMonster")
		TArray<AMonsterSpawnActor*> SpawnMonsterArray;


	////����� FieldArea ã��
	//AFieldArea* FindClosestMonsterArea();
	UPROPERTY(EditAnywhere, Category = "MyArea")
	AFieldArea* MyArea;

	//Area���� �� ��Ҵ���
	UPROPERTY(BlueprintReadOnly)
	bool AreaClear;

	//óġ�� ���� ��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int numberOfMonstersDefeafed;

private:
	bool bIsOn;

	UPROPERTY(VisibleAnywhere)
	bool bIsMonsterSpawned;

	UPROPERTY(EditAnywhere)
		USceneComponent* _RootComponent;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* InteractionSampleMesh;
	UPROPERTY(EditAnywhere)
		UWidgetComponent* InteractionWidget;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "InteractionObj")
	void BattleStart();
	UFUNCTION(BlueprintImplementableEvent, Category = "InteractionObj")
	void BattleEnd();
};
