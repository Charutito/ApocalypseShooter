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
        GetBlackboardComponent()->SetValueAsVector(TEXT("FirstLocation"), GetPawn()->GetActorLocation());
    }
}

void AZombieAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
