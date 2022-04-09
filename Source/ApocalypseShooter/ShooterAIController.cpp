#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"


void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    MoveToPlayerIfInSight();
}

void AShooterAIController::MoveToPlayerIfInSight()
{
    if (LineOfSightTo(PlayerPawn))
    {
        MoveToActor(PlayerPawn, AcceptanceRadius);
        SetFocus(PlayerPawn);
    }
    else
    {
        StopMovement();
        ClearFocus(EAIFocusPriority::Gameplay);
    }
}