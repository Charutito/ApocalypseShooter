#include "ZombieAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AZombieAIController::BeginPlay()
{
    Super::BeginPlay();
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (AIBehaviour != nullptr)
    {
        RunBehaviorTree(AIBehaviour);
        GetBlackboardComponent()->SetValueAsVector(TEXT("FirstLocation"), GetOwner()->GetActorLocation());
    }
}

void AZombieAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    MoveToPlayerIfInSight();
}

void AZombieAIController::MoveToPlayerIfInSight()
{
    if (LineOfSightTo(PlayerPawn))
    {
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
    }
    else
    {
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    }
}