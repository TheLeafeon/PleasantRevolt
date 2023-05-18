// Fill out your copyright notice in the Description page of Project Settings.

#include "Teleporter.h"
#include "Kismet/GameplayStatics.h"
#include "CharMoveTest/Player/PlayerableCharacter.h"

// Sets default values
ATeleporter::ATeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root component"));
	RootComponent = _RootComponent;

	TeleportIn = CreateDefaultSubobject<UBoxComponent>(TEXT("Teleport IN"));
	TeleportIn->SetupAttachment(RootComponent);

	TeleportOut = CreateDefaultSubobject<UBoxComponent>(TEXT("Teleport Out"));
	TeleportOut->SetupAttachment(RootComponent);

	TargetTeleporter = nullptr;
}

// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();

	TeleportIn->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnBoxBeginOverlap);
}

// Called every frame
void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ATeleporter::GetOutLocation()
{
	return TeleportOut->GetComponentLocation();
}

void ATeleporter::ActorTeleport(AActor* target)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Debug"));

	if (!TargetTeleporter)
		return;
	if (!target)
		return;

	FVector NewLocation = TargetTeleporter->GetOutLocation();
	USceneComponent* OtherComp = target->GetRootComponent();
	OtherComp->SetWorldLocation(NewLocation);
	//target->SetActorLocation(NewLocation);
}

void ATeleporter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,TEXT("Debug"));
	if (!TargetTeleporter)
		return;
	if (!OtherActor->ActorHasTag("Player"))
		return;

	FVector NewLocation = TargetTeleporter->GetOutLocation();
	OtherActor->SetActorLocation(NewLocation);
}