#include "ZombieCharacter.h"

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
	UE_LOG(LogTemp, Warning, TEXT("ATTACK WACHO"));
}
