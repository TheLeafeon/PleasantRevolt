// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldName.h"

// Sets default values
AFieldName::AFieldName()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FieldName = FText();
}

// Called when the game starts or when spawned
void AFieldName::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFieldName::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

