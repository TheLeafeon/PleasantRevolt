
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Basket.generated.h"

UCLASS()
class CHARMOVETEST_API ABasket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* PlayerSit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BasketOverlapBoxSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TargetActorLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StudioTargetActorLocation;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Basket �̵�
	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MoveBasket();

	//���� �� �ٽ� �����̵��� ���� ���� �ϴ� �Լ� BP���� ����
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StudioTeleport();

	UPROPERTY(EditAnywhere, Category = "TargetLocation")
	class AActor* TargetActor;

	UPROPERTY(EditAnywhere, Category = "StudioTargetLocation")
	class AActor* StudioTargetActor;

	FTimerHandle BasketMoveHandle;
	

	//Basket 1ȸ ũ�� ������
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BasketRotationChange();


	//Bakset ���Ÿ� �ݺ�
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BasketShakeLoop();

private:
	bool firstIn;

};
