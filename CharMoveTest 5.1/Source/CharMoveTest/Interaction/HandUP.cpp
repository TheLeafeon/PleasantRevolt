// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Interaction/HandUP.h"

// Sets default values
AHandUP::AHandUP() : IsHandUp(false), IsMirror(false)
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
	if (PlayerCharacter->IsHandUp && IsHandUp && IsUpActor == this)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
			{	
				//CollisionComponent->SetCollisionProfileName(TEXT("InteractionObj_B"));
				BlockCollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));

				const FRotator Rotation = PlayerCharacter->GetActorRotation();
				const FRotator YawRotation(0, Rotation.Yaw, 0);

				// get forward vector
				const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * 150;
				
				SetActorLocation(PlayerCharacter->GetActorLocation() + Direction);
				SetActorRotation(/*FRotator(0, 0, GetActorRotation().Pitch)*/ PlayerCharacter->GetActorRotation());

				GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
					{
						CollisionComponent->SetSimulatePhysics(true);

						CollisionComponent->AddImpulse(GetActorForwardVector() * 300, "None", true);

						GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
						GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
							{
								//CollisionComponent->SetSimulatePhysics(false);
								
								if (IsMirror)
								{
									SetMirrorHandUp();
								}

								GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
							}), 1.5f, false);
					}), 0.15f, false);
					
			}), 0.65f, false);
			
		HandUpAni(false);

		IsHandUp = false;
		PlayerCharacter->SetIsHandUp(false);
	}
	else if (PlayerCharacter->IsHandUp == false && !IsHandUp)
	{	
		//CollisionComponent->SetCollisionProfileName(TEXT("InteractionObj_O"));
		BlockCollisionComponent->SetCollisionProfileName(TEXT("OverlapAll"));
		CollisionComponent->SetSimulatePhysics(false);
		PlayerCharacter->PlayerHandUp(this);
		PlayerCharacter->SetIsHandUp(true);
		IsUpActor = PlayerCharacter->HandUpObj;

		HandUpAni(true);

		IsHandUp = true;
		
		if (IsMirror)
		{
			DestroyMirrorHandUp();
		}

		HideInteractionWidget();
	}
	
}

void AHandUP::ShowInteractionWidget()
{
	if (!IsHandUp)
	{
		InteractionWidget->SetVisibility(true);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("You press E"));
}

void AHandUP::HideInteractionWidget()
{
	InteractionWidget->SetVisibility(false);
}

void AHandUP::SetFalsePhysics()
{
	CollisionComponent->SetSimulatePhysics(false);
}

void AHandUP::Drop()
{
	if (IsHandUp)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		//CollisionComponent->SetCollisionProfileName(TEXT("InteractionObj_B"));
		BlockCollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));

		const FRotator Rotation = PlayerCharacter->GetActorRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * 150;

		SetActorLocation(PlayerCharacter->GetActorLocation() + Direction);
		SetActorRotation(FRotator(0, 0, GetActorRotation().Yaw));


		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
			{
				CollisionComponent->SetSimulatePhysics(true);

				GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
					{
						CollisionComponent->SetSimulatePhysics(false);
						
						if (IsMirror)
						{
							SetMirrorHandUp();
						}

						GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
					}), 1.5f, false);
			}), 0.2f, false);

		HandUpAni(false);

		IsHandUp = false;
	}
}

void AHandUP::BackDrop()
{
	if (IsHandUp)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		//CollisionComponent->SetCollisionProfileName(TEXT("InteractionObj_B"));
		BlockCollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));

		const FRotator Rotation = PlayerCharacter->GetActorRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * -150;

		SetActorLocation(PlayerCharacter->GetActorLocation() + Direction);
		SetActorRotation(FRotator(0, 0, GetActorRotation().Yaw));


		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
			{
				CollisionComponent->SetSimulatePhysics(true);

				GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]()
					{
						CollisionComponent->SetSimulatePhysics(false);
						
						if (IsMirror)
						{
							SetMirrorHandUp();
						}

						GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
					}), 1.5f, false);
			}), 0.2f, false);

		HandUpAni(false);

		IsHandUp = false;
	}
}