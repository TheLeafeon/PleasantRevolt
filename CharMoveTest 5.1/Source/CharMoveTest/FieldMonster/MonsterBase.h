// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MonsterBase.generated.h"

UCLASS()
class CHARMOVETEST_API AMonsterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterBase();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster_Information")
		float Monster_Power;

	//체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster_Information")
		float Monster_HP;

	//이동속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster_Information")
		float Monster_Speed;

	//공격 사정거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster_Attack_Information")
		FVector Monster_Attack_Distance;

	//공격 시간: 공격중->공격상태 로 변하는 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster_Attack_Information")
		float Monster_Attack_Time;

	//공격 딜레이: 공격 실행 중인 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster_Attack_Information")
		float Monster_Attack_Delay;

	//피격 시 넉백 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster_Attack_Information")
		FVector Monster_Knockback_Distance;

	//피격 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster_Attack_Information")
		float Monster_Knockback_Time;



	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
