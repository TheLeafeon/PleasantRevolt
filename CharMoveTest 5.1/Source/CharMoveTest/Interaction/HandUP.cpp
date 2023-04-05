// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Interaction/HandUP.h"

// Sets default values
AHandUP::AHandUP() : IsHandUp(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHandUP::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerableCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	AnimInstance = Cast<UPlayerAnimInstnce>(PlayerCharacter->GetMesh()->GetAnimInstance());
}

// Called every frame
void AHandUP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHandUP::InteractWithMe()
{
	if (IsHandUp)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CollisionComponent->SetCollisionProfileName(TEXT("InteractionObj_B"));
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("IsHandUp"));

		//���� �ִϸ��̼� �������°� ������ �� �����ϱ�
		SetActorLocation(PlayerCharacter->GetActorLocation() + (PlayerCharacter->GetActorForwardVector() * 10));

		CollisionComponent->SetSimulatePhysics(true);
		//1�� �� ������ ����(�׷��� �������� ����)!
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
			{

				CollisionComponent->SetSimulatePhysics(false);

			}), 1.0f, false);

		HandUpAni(false);

		IsHandUp = false;
	}
	else
	{
		CollisionComponent->SetSimulatePhysics(false);
		CollisionComponent->SetCollisionProfileName(TEXT("InteractionObj_O"));
		PlayerCharacter->PlayerHandUp(this);
		//AnimInstance->PlayHandUpMontage();
		HandUpAni(true);

		IsHandUp = true;
	}
	
}

void AHandUP::ShowInteractionWidget()
{
	//InteractionWidget->SetVisibility(true);

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("You press E"));

}

void AHandUP::HideInteractionWidget()
{
	//InteractionWidget->SetVisibility(false);
}

void AHandUP::SetFalsePhysics()
{
	CollisionComponent->SetSimulatePhysics(false);
}