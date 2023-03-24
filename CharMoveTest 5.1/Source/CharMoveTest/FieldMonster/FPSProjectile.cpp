// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // ��ü�� �ܼ� �ݸ��� ǥ������ ����մϴ�.
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    
    CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
    CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);


    // ��ü�� �ݸ��� �ݰ��� �����մϴ�.
    CollisionComponent->InitSphereRadius(15.0f);
    // ��Ʈ ������Ʈ�� �ݸ��� ������Ʈ�� �����մϴ�.
    RootComponent = CollisionComponent;

    // ProjectileMovementComponent �� ����Ͽ� �� �߻�ü�� ��� �����մϴ�.
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
    ProjectileMovementComponent->InitialSpeed = 3000.0f;
    ProjectileMovementComponent->MaxSpeed = 3000.0f;
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->bShouldBounce = true;
    ProjectileMovementComponent->Bounciness = 0.3f;

    //3�� �� źȯ ��ü ����
    InitialLifeSpan = 0.1f;
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// ������Ÿ���� �ӵ��� �߻� �������� �ʱ�ȭ��Ű�� �Լ��Դϴ�.
void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
    ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

//// ������Ÿ���� ���𰡿� ������ ȣ��Ǵ� �Լ��Դϴ�.
void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{

    //OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
    //GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Attack!"));
    OnCollision(Hit);
}

void AFPSProjectile::OnCollision(const FHitResult& HitResult)
{
    Destroy();
}

