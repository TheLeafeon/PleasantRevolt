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
	    // 프로젝타일 발사를 시도합니다.
    if (ProjectileClass)
    {
        // 카메라 트랜스폼을 구합니다.
        FVector DragonDollHeadLocation;
        FRotator DragonDollHeadRotation;
        GetActorEyesViewPoint(DragonDollHeadLocation, DragonDollHeadRotation);

        // MuzzleOffset 을 카메라 스페이스에서 월드 스페이스로 변환합니다.
        FVector MuzzleLocation = DragonDollHeadLocation + FTransform(DragonDollHeadRotation).TransformVector(MuzzleOffset);
        FRotator MuzzleRotation = DragonDollHeadRotation;

        //// 조준을 약간 윗쪽으로 올려줍니다.
        MuzzleRotation.Pitch += 10.0f;
        UWorld* World = GetWorld();
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();

            // 총구 위치에 발사체를 스폰시킵니다.
            AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
            if (Projectile)
            {
                // 발사 방향을 알아냅니다.
                FVector LaunchDirection = MuzzleRotation.Vector();
                Projectile->FireInDirection(LaunchDirection);
            }
        }
    }
}
