// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/DragonDoll.h"
#include "CharMoveTest/CharMoveTest.h"
#include "DrawDebugHelpers.h"
#include "CharMoveTest/FieldMonster/DragonDollAIController.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "TimerManager.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Engine.h"



ADragonDoll::ADragonDoll()
{

    AIControllerClass = ADragonDollAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    DragonDollHead = CreateDefaultSubobject<UCameraComponent>(TEXT("DragonHead"));
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
void ADragonDoll::BeginPlay()
{
    Super::BeginPlay();
    int TestNum = 100;

    MyArea = FindClosestMonsterArea();
    MyAreaSize = MyArea->CollisionBox->GetScaledBoxExtent();
    MyAreaLocation = MyArea->GetActorLocation();


    //GirlDoll�� ���������� �ڶ󳪵��� ����
    FVector DragonDollSpawnStartLocation = GetActorLocation();
    StartZLocation = DragonDollSpawnStartLocation.Z;
    DragonDollSpawnStartLocation.Z = DragonDollSpawnStartLocation.Z - 200.0f;
    SetActorLocation(DragonDollSpawnStartLocation);

    SetActorEnableCollision(false);
    //�ڶ󳪱� Ÿ�̸�
    //FTimerHandle GirlDollSpawnMoveUpHandle;


    FTimerDelegate DragonDollSpawnMoveUpDelegate = FTimerDelegate::CreateUObject(this, &ADragonDoll::DragonDollSpawnEffect);
    GetWorldTimerManager().SetTimer(DragonDollSpawnMoveUpHandle, DragonDollSpawnMoveUpDelegate, 0.01f, true);

}

void ADragonDoll::Attack_Melee()
{
    // ������Ÿ�� �߻縦 �õ��մϴ�.
    if (ProjectileClass)
    {
        FTimerHandle AttackTimerHandle;

        Fire();

        FTimerDelegate AttackTimerDelegate = FTimerDelegate::CreateUObject(this, &ADragonDoll::AttackTimer);
        GetWorldTimerManager().SetTimer(AttackTimerHandle, AttackTimerDelegate, 4.0f, false);


    }
}

void ADragonDoll::AttackTimer()
{
    DragonDollOnAttackEnd.Broadcast();
}

AFieldArea* ADragonDoll::FindClosestMonsterArea()
{
    TArray<AActor*> OverlappingActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFieldArea::StaticClass(), OverlappingActors);

    AFieldArea* ClosestArea = nullptr;
    FVector DragonDollLocation = GetActorLocation();

    float MinDistance = TNumericLimits<float>::Max();

    for (AActor* Actor : OverlappingActors)
    {
        AFieldArea* Area = Cast<AFieldArea>(Actor);
        if (Area != nullptr)
        {
            float Distance = FVector::Distance(DragonDollLocation, Area->GetActorLocation());
            if (Distance < MinDistance)
            {
                MinDistance = Distance;
                ClosestArea = Area;
            }
        }
    }

    return ClosestArea;
}

void ADragonDoll::DragonDollSpawnEffect()
{
    FVector DragonDollSpawnStartLocation = GetActorLocation();
    float CurrentZ = DragonDollSpawnStartLocation.Z;
    float TargetZ = StartZLocation; // ��ǥ ��ġ
    float Speed = 10.f; // �̵� �ӵ� (1�ʿ� 1000��ŭ �̵�)

    float DeltaZ = Speed * GetWorld()->GetDeltaSeconds();
    float NewZ = FMath::FInterpTo(CurrentZ, TargetZ, GetWorld()->GetDeltaSeconds(), Speed);
    DragonDollSpawnStartLocation.Z = NewZ;

    SetActorLocation(DragonDollSpawnStartLocation);

    if (FMath::IsNearlyEqual(NewZ, TargetZ, 0.1f)) // ��ǥ ��ġ�� �������� �� Ÿ�̸� ����
    {
        SetActorEnableCollision(true);
        GetWorld()->GetTimerManager().ClearTimer(DragonDollSpawnMoveUpHandle);
    }
}

float ADragonDoll::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    const float DragonDollGetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

    if (Monster_HP <= 0.0f)
    {
        return 0.0f;
    }

    if (DragonDollGetDamage > 0.0f)
    {
        Monster_HP -= DragonDollGetDamage;
    }

    if (Monster_HP <= 0)
    {
        MyArea->numberOfMonstersDefeafed = MyArea->numberOfMonstersDefeafed + 1;
        //Die(getDamage, DamgaeEvent, EventInstigator, DamageCauser);
        Destroy();
    }
    else
    {
        OnHit(DragonDollGetDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
    }

    return DragonDollGetDamage;
}

void ADragonDoll::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
    if (DamageTaken > 0.0f)
    {
        ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
    }
}
