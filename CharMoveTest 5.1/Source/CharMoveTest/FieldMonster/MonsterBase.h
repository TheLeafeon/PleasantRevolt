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

	//���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster_Information")
		float Monster_Power;

	//ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster_Information")
		float Monster_HP;

	//�̵��ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster_Information")
		float Monster_Speed;

	//���� �����Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster_Attack_Information")
		FVector Monster_Attack_Distance;

	//���� �ð�: ������->���ݻ��� �� ���ϴ� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster_Attack_Information")
		float Monster_Attack_Time;

	//���� ������: ���� ���� ���� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster_Attack_Information")
		float Monster_Attack_Delay;

	//�ǰ� �� �˹� �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster_Attack_Information")
		FVector Monster_Knockback_Distance;

	//�ǰ� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster_Attack_Information")
		float Monster_Knockback_Time;



	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
