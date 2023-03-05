// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerAnimInstnce.h"
#include "Components/TimeLineComponent.h"
#include "GameFramework/Character.h"
#include "PlayerableCharacter.generated.h"

class UCurveFloat;

UCLASS()
class CHARMOVETEST_API APlayerableCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
public:
	APlayerableCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

protected:
	void BeginPlay() override;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/* Player Rolling */
	void Rolling();

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

private :
	UPlayerAnimInstnce* AnimInstance;

/* Player Rolling Timeline */
protected :
	UFUNCTION()
		void TimelineProgress(float Value);

	FTimeline CurveTimeline;
	UPROPERTY(EditAnywhere, Category = "Timeline")
		UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, Category = "Timeline")
		float ZOffset;

private :
	UPROPERTY(EditAnywhere, Category = "Status")
		float Player_HP;
	UPROPERTY(EditAnywhere, Category = "Status")
		float Player_Speed;
	UPROPERTY(EditAnywhere, Category = "Status")
		float Player_Roll_Test;
	UPROPERTY(EditAnywhere, Category = "Status")
		float Player_Attack_Power;
	UPROPERTY(EditAnywhere, Category = "Status")
		float Player_Attack_Near_Distance;
	UPROPERTY(EditAnywhere, Category = "Status")
		float Player_Attack_Far_Distance;

public :
	UFUNCTION(BlueprintCallable, Category = "Status")
		float Get_Player_HP();
	UFUNCTION(BlueprintCallable, Category = "Status")
		void Increase_Player_HP(float val);
	UFUNCTION(BlueprintCallable, Category = "Status")
		void Decrease_Player_HP(float val);

	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamgaeEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	UFUNCTION(BlueprintCallable)
		virtual float TakeDamage(float Damage, struct FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);
	void DeathEnd();

private :
	bool isAttack;

	UFUNCTION(BlueprintCallable)
		void Attack_Melee();
	void Attack_Melee_End();
	UFUNCTION(BlueprintCallable)
		void Attack_Shooting();
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};