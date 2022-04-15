#include "BaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "ApocalypseShooterGameModeBase.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ABaseCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(CurrentHealth, DamageApplied);
	CurrentHealth -= DamageApplied;
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), CurrentHealth);

	if (IsDead())
	{
		NotifyDeadToGameMode();
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);		
	}

	return DamageApplied;
}

bool ABaseCharacter::IsDead() const
{
	return CurrentHealth <= 0;
}

void ABaseCharacter::NotifyDeadToGameMode()
{
	AApocalypseShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AApocalypseShooterGameModeBase>();
	if (GameMode != nullptr)
	{
		GameMode->PawnKilled(this);
	}
}