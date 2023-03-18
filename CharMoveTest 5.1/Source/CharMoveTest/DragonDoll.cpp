// Fill out your copyright notice in the Description page of Project Settings.


#include "DragonDoll.h"
#include "TestCharacter.h"
#include "DrawDebugHelpers.h"

#include "Engine/World.h"
#include "Engine.h"



ADragonDoll::ADragonDoll()
{

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    DragonDollHead  = CreateDefaultSubobject<UCameraComponent>(TEXT("DragonHead"));
    DragonDollHead->SetupAttachment(GetCapsuleComponent());
    DragonDollHead->SetRelativeLocation(FVector(50.0f, 0.0f, -20.0f + BaseEyeHeight));
    DragonDollHead->bUsePawnControlRotation = true;


	Monster_HP = 2.0f;
	Monster_Power = 1.0f;
	Monster_Speed = 1.0f;
	Monster_Attack_Time = 0.0f;
	Monster_Attack_Delay = 5.0f;
	Monster_Knockback_Time = 0.0;
}
void ADragonDoll::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ADragonDoll::Fire);

}
void ADragonDoll::Fire()
{
	    // ������Ÿ�� �߻縦 �õ��մϴ�.
    if (ProjectileClass)
    {
        // ī�޶� Ʈ�������� ���մϴ�.
        FVector DragonDollHeadLocation;
        FRotator DragonDollHeadRotation;
        GetActorEyesViewPoint(DragonDollHeadLocation, DragonDollHeadRotation);

        // MuzzleOffset �� ī�޶� �����̽����� ���� �����̽��� ��ȯ�մϴ�.
        FVector MuzzleLocation = DragonDollHeadLocation + FTransform(DragonDollHeadRotation).TransformVector(MuzzleOffset);
        FRotator MuzzleRotation = DragonDollHeadRotation;

        //// ������ �ణ �������� �÷��ݴϴ�.
        MuzzleRotation.Pitch += 10.0f;
        UWorld* World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();

            // �ѱ� ��ġ�� �߻�ü�� ������ŵ�ϴ�.
            AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
            if (Projectile)
            {
                // �߻� ������ �˾Ƴ��ϴ�.
                FVector LaunchDirection = MuzzleRotation.Vector();
                Projectile->FireInDirection(LaunchDirection);
            }
        }
    }
}
