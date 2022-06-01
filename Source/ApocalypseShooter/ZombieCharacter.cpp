#include "ZombieCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

AZombieCharacter::AZombieCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AZombieCharacter::BeginPlay()
{
	Super::BeginPlay();
	BaseSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void AZombieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZombieCharacter::Attack()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	if (PlayerPawn == nullptr) return;

	float DistanceToPlayer = FVector::Distance(GetActorLocation(), PlayerPawn->GetActorLocation());

	if (DistanceToPlayer <= AttackRange)
	{
		FDamageEvent DamageEvent;
		PlayerPawn->TakeDamage(Damage, DamageEvent, GetController(), this);
	}
}

float AZombieCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (!IsDead())
	{
		FVector Location = GetActorLocation() + FVector(0.f, 0.f, DamageTextPositionOffset);
		FRotator Rotation = GetActorRotation();
		GetWorld()->SpawnActor<AActor>(DamageFloatingText, Location, Rotation);
	}

	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	GetHit(true);

	return DamageApplied;
}

void AZombieCharacter::SetIdleState(bool isIdle)
{
	IsIdle = isIdle;
}

void AZombieCharacter::SetChasingState(bool isChasing)
{
	IsChasing = isChasing;
}

void AZombieCharacter::GetHit(bool isHitted)
{
	IsReactingToHit = isHitted;

	if (isHitted)
	{
		GetCharacterMovement()->MaxWalkSpeed = 0;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
	}
}