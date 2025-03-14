// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/FieldMonster/FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // 구체를 단순 콜리전 표현으로 사용합니다.
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    
    CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
    CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);


    // 구체의 콜리전 반경을 설정합니다.
    //CollisionComponent->InitSphereRadius(15.0f);
    // 루트 컴포넌트를 콜리전 컴포넌트로 설정합니다.
    RootComponent = CollisionComponent;

    // ProjectileMovementComponent 를 사용하여 이 발사체의 운동을 관장합니다.
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
    ProjectileMovementComponent->InitialSpeed = 3000.0f;
    ProjectileMovementComponent->MaxSpeed = 3000.0f;
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
    ProjectileMovementComponent->bShouldBounce = true;
    ProjectileMovementComponent->Bounciness = 0.3f;

    //3초 후 탄환 구체 삭제
    InitialLifeSpan = 0.1f;

    Fire_Power = 1.0f;
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSProjectile::FarmannequinProjectile()
{
    ProjectileMovementComponent->MaxSpeed = 1500.0f;
    ProjectileMovementComponent->ProjectileGravityScale = 0.2;
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// 프로젝타일의 속도를 발사 방향으로 초기화시키는 함수입니다.
void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
    ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

//// 프로젝타일이 무언가에 맞으면 호출되는 함수입니다.
void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{

    //OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
    //GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Attack!"));
    OnCollision(Hit);
}

void AFPSProjectile::OnCollision(const FHitResult& HitResult)
{
    //Destroy();
}

