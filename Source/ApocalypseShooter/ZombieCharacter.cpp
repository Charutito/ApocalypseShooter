#include "ZombieCharacter.h"
#include "Kismet/GameplayStatics.h"

AZombieCharacter::AZombieCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AZombieCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AZombieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZombieCharacter::Attack()
{
	IsAttacking = true;
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	float DistanceToPlayer = FVector::Distance(GetActorLocation(), PlayerPawn->GetActorLocation());

	if (DistanceToPlayer <= AttackRange)
	{
		FDamageEvent DamageEvent;
		PlayerPawn->TakeDamage(Damage, DamageEvent, GetController(), this);
	}
}
