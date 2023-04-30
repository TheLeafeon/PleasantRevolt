
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

	//Basket 이동
	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MoveBasket();

	//공격 후 다시 움직이도록 변수 변경 하는 함수 BP에서 정의
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StudioTeleport();

	UPROPERTY(EditAnywhere, Category = "TargetLocation")
	class AActor* TargetActor;

	UPROPERTY(EditAnywhere, Category = "StudioTargetLocation")
	class AActor* StudioTargetActor;

	FTimerHandle BasketMoveHandle;
	

	//Basket 1회 크게 움직임
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BasketRotationChange();


	//Bakset 흔들거림 반복
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BasketShakeLoop();

private:
	bool firstIn;

};
