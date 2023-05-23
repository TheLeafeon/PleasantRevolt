// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Interaction/HandUP.h"

// Sets default values
AHandUP::AHandUP() : IsHandUp(false), IsMirror(false), IsDown(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHandUP::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerableCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter != nullptr)
	{
		AnimInstance = Cast<UPlayerAnimInstnce>(PlayerCharacter->GetMesh()->GetAnimInstance());
	}

}

// Called every frame
void AHandUP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDown)
	{
		if (FMath::IsNearlyEqual(GetActorRotation().Roll, 0.0f, 5.0f) && FMath::IsNearlyEqual(GetActorRotation().Pitch, 0.0f, 5.0f))
		{
			CollisionComponent->SetSimulatePhysics(false);
			IsDown = false;
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("!!!!!!!!!"));
		}
	}
}

void AHandUP::InteractWithMe()
{
	if (PlayerCharacter->IsHandUp && IsHandUp /* && PlayerCharacter->HandUpObj == this*/)
	{
		DestroyMirrorHandUp();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("down"));
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
								IsDown = true;

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
		PlayerCharacter->IsHandUp = false;
		PlayerCharacter->SetInterface();
	}
	else if (PlayerCharacter->IsHandUp == false && !IsHandUp)
	{	
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, TEXT("up"));
		//CollisionComponent->SetCollisionProfileName(TEXT("InteractionObj_O"));
		BlockCollisionComponent->SetCollisionProfileName(TEXT("OverlapAll"));
		CollisionComponent->SetSimulatePhysics(false);
		PlayerCharacter->PlayerHandUp(this);
		HideInteractionWidget();

		HandUpAni(true);

		IsHandUp = true;
	}
	
}

void AHandUP::ShowInteractionWidget()
{
	if (!IsHandUp && PlayerCharacter->IsHandUp == false)
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
		DestroyMirrorHandUp();
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
		PlayerCharacter->IsHandUp = false;
	}
}

void AHandUP::BackDrop()
{
	if (IsHandUp)
	{
		DestroyMirrorHandUp();
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
		PlayerCharacter->IsHandUp = false;
	}
}