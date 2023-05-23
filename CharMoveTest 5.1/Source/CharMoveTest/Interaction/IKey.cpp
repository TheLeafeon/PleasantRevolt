// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Interaction/IKey.h"

// Sets default values
AIKey::AIKey() : IsGet(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIKey::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIKey::InteractWithMe()
{
	if (!IsGet)
	{
		IsGet = true;
		CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

		HideInteractionWidget();
	}
}

void AIKey::ShowInteractionWidget()
{
	if (!IsGet)
	{
		InteractionWidget->SetVisibility(true);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("You press E"));
}

void AIKey::HideInteractionWidget()
{
	InteractionWidget->SetVisibility(false);
}