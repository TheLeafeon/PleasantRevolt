// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestCharacter.generated.h"



UCLASS()
class CHARMOVETEST_API ATestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestCharacter();



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Camera)
	class UCameraComponent* FollowCamera;

	//문 열리면 카메라 이동, 이동 지점
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MoveCamera(FVector TargetPoint);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	void MoveForward(float Value);

	void MoveRight(float Value);

	void TryInteraction();
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CharMoveAllow=true;

	UPROPERTY(BlueprintReadWrite)
	FVector AttachmentCameraLocation;
	
	
};
