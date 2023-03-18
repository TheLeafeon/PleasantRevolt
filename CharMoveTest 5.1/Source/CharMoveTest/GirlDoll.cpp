
#include "GirlDoll.h"
#include "Components/BoxComponent.h"
#include "TestCharacter.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Engine.h"

AGirlDoll::AGirlDoll()
{
	AIControllerClass = AGirlDollAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	/*MyArea = nullptr;*/
	Monster_HP = 3.0f;
	Monster_Power = 1.0f;
	Monster_Speed = 2.0f;
	Monster_Attack_Time = 1.0f;
	Monster_Attack_Delay = 0.5f;
	Monster_Knockback_Time = 0.5;
	AttackRangeBoxSize = FVector(100.0f, 100.0f, 100.0f);

	AttackRange = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackRange"));
	

	AttackRange->SetBoxExtent(AttackRangeBoxSize);
	AttackRange->SetupAttachment(GetMesh());

	isReadyAttack = false;
	isDuringAttack = false;

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Spawn")));

	//CheckMonsterArea();

}

float AGirlDoll::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float myGetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);


	if (Monster_HP <= 0)
	{
		this->Destroy();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("HP: %f"), Monster_HP));
		Monster_HP -= myGetDamage;
	}

	return myGetDamage;
}





void AGirlDoll::Attack_Ready()
{
	isReadyAttack = true;

	
}

void AGirlDoll::Attack_Melee()
{
	isDuringAttack = true;

	isReadyAttack = false;

	AttackRange->OnComponentBeginOverlap.AddDynamic(this, &AGirlDoll::OnOverlapBegin);
}

void AGirlDoll::Attack_Melee_End()
{
	isDuringAttack = false;
}



void AGirlDoll::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("Attack!"));

}


