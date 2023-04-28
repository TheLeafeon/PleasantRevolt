// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerAnimInstnce.h"
#include "InteractionInterface.h"
#include "WeaponInterface.h"
#include "WeaponBase.h"
#include "Components/BoxComponent.h"
#include "Components/TimeLineComponent.h"
#include "GameFramework/Character.h"
#include "PlayerableCharacter.generated.h"

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

	void Tick(float DeltaTime) override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/*
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

//**************** bool 변수들 ***********************//
private :
	bool bisHit;
	bool bisDie;
	bool isWeaponChanging;
	bool bIsRolling;
	bool isDodge;
public :
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MeleeAttack")
		bool bisAttack;
//****************************************************//

//************** 행동중인지 판단  *******************//
private :
	std::vector<bool> actions;
	bool bCanAction();
//****************************************************//

private :
	void LookMousePosition();

private :
	// 플레이어의 애니메이션을 저장해둔 것
	UPlayerAnimInstnce* AnimInstance;
	APlayerController* PlayerController;
	// Timer남은시간
	float RemainingTime;
/* Player Rolling */
protected :
	// Player Roll Function
	void Rolling();

	UFUNCTION()
		void TimelineProgress(float Value);

	// 잉여 데이터
	FTimeline CurveTimeline;
	UCurveFloat* CurveFloat;

	// Declare a reference to the timeline and the curve float that will be used for the roll animation
	UPROPERTY(EditAnywhere, Category = "Rolling")
		UCurveFloat* RollCurve;
	FTimeline RollTimeline;

	// Declare variables for the start and end rotations of the roll animation
	FRotator StartRotation;
	FRotator EndRotation;

	// Declare a variable to store the length of the roll animation
	float RollAnimationLength = 1.0f;

	// 타이머 설정을 위한 TimerHandle
	FTimerHandle RollTimerHandle;
	
	float UpdateRollCurve(float Value);
public :
	// 플레이어 구르기 종료 후
	void EnableInputAfterRoll();

/* Player Status */
private :
	UPROPERTY(EditAnywhere, Category = "Status")
		float Player_HP;
	UPROPERTY(EditAnywhere, Category = "Status")
		float Player_Roll_Time;

/* Player Dodge */
	UPROPERTY(EditAnywhere, Category = "Status")
		float Player_Dodge_Time;

	FTimerHandle DodgeTimerHandle;

	void DodgeStart(const float& time);
	void DodgeEnd();
	
/* Player Get Damage & Die 관련 */
public :
	// 플레이어의 체력을 밖으로 보내기 위위해서 작성
	UFUNCTION(BlueprintCallable, Category = "Status")
		float Get_Player_HP();
	// 플레이어의 체력이 증가하는지 확인
	UFUNCTION(BlueprintCallable, Category = "Status")
		void Increase_Player_HP(float val);

	// 히트 판정
	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamgaeEvent, class APawn* PawnInstigator, class AActor* DamageCauser);
	// Get Damage
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamgaeEvent, AController* EventInstigator, AActor* DamageCauser) override;
	// 플레이어 사망
	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);
	// 플레이어 사망 애니메이션 종료 시 발생하는 함수
	void DeathEnd();

	FTimerHandle DeathTimerHandle;

/* Player Attack 관련 */
public :
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MeleeAttack")
		int32 currentCombo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttack")
		float comboCoolTime;

	UFUNCTION(BlueprintCallable)
		void Attack_Melee_End();
	UFUNCTION(BlueprintCallable)
		void Enable_Attack_Enemy();
	UFUNCTION(BlueprintCallable)
		void Disable_Attack_Enemy();
private :
	// Weapon관련 interface
	IWeaponInterface* WeaponInterface;

	// Weapon 객체 보관 배열
	UPROPERTY(EditAnywhere, Category = "Weapons")
		TArray<AWeaponBase*> MeleeWeaponsArray;

	const int32 FIRST_WEAPON = 0;
	const int32 SECOND_WEAPON = 1;
	const int32 THIRD_WEAPON = 2;

	// Weapon 1, 2, 3
	UPROPERTY(EditAnywhere, Category = "Weapons")
		TSubclassOf<class AWeaponBase> FirstWeapon;
	UPROPERTY(EditAnywhere, Category = "Weapons")
		TSubclassOf<class AWeaponBase> SecondWeapon;
	UPROPERTY(EditAnywhere, Category = "Weapons")
		TSubclassOf<class AWeaponBase> ThirdWeapon;
	UPROPERTY(EditAnywhere, Category = "Weapons")
		TSubclassOf<class AWeaponBase> SubWeapon;

	// 현재 장착중인 무기 확인용
	UPROPERTY(VisibleAnywhere, Category = "Weapons")
		class AWeaponBase* CurrentWeapon;
	UPROPERTY(VisibleAnywhere, Category = "Weapons")
		class AWeaponBase* CurrentSubWeapon;

	class UAnimMontage* CurrentWeaponComboAnim;

	void SwitchWeapon(int32 WeaponIndex);
	void FirstMeleeWeapon();
	void SecondMeleeWeapon();
	void ThirdMeleeWeapon();
	void EquipSubWeapon();
	void UnEquipSubWeapon();
	int32 maxCombo;
	FTimerHandle NextComboTimerHandle;

	UFUNCTION(BlueprintCallable)
		void Attack_Melee();
	UFUNCTION(BlueprintCallable)
		void Attack_Shooting();

/* Interaction System 관련 */
private :
	// 상호작용을 위한 박스 컴포넌트
	UPROPERTY(EditAnywhere)
		UBoxComponent* InteractionBox;

	// 인터페이스를 통해서 상호작용 연결
	IInteractionInterface* Interface;

	// 상호작용 박스가 겹쳤는지 확인하고 상호작용
	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// 상호작용 박스에서 벗어났는지 확인하고 상호작용
	UFUNCTION()
		void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// 상호작용 키를 눌렀을 때 작동하는 함수
	void OnInteract();
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//virtual void CharacterMovementComponent() override;

	//HandUp관련
	UFUNCTION()
	void PlayerHandUp(AActor* OtherActor);
	UPROPERTY(BlueprintReadWrite)
	AActor* HandUpObj;
	UFUNCTION(BlueprintImplementableEvent)
	void HitDrop();
	UFUNCTION(BlueprintImplementableEvent)
	void SetAnimIsDrop(bool IsDrop);

private:
	//Ladder관련
	UPROPERTY()
	bool isLadder;
	UFUNCTION()
	void LadderMove(float Value);
	UPROPERTY()
	float SaveZLocation;
public:
	UPROPERTY(BlueprintReadWrite, Category = "Ladder")
	bool StopLadderMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ladder")
	float LadderMoveSpeed;
	UFUNCTION(BlueprintCallable)
	void SetLadderMoveTrue();
	UFUNCTION(BlueprintCallable)
	void SetLadderMoveFalse();
	UPROPERTY(BlueprintReadWrite, Category = "Ladder")
	bool LadderStart;
};