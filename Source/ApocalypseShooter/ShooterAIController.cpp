#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (AIBehaviour != nullptr)
    {
        RunBehaviorTree(AIBehaviour);
        GetBlackboardComponent()->SetValueAsVector(TEXT("FirstLocation"), FirstLocation);
    }
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
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());

        //GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));

        //MoveToActor(PlayerPawn, 200);
        //SetFocus(PlayerPawn);
    }
    else
    {
        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));

        //StopMovement();
        //ClearFocus(EAIFocusPriority::Gameplay);
    }
}