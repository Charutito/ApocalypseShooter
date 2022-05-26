#include "BTService_PlayerLocationIfSeen.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ZombieCharacter.h"
#include "AIController.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
    AAIController* Controller = OwnerComp.GetAIOwner();
    
    if (Controller == nullptr)
    {
        return;
    }

    AZombieCharacter* Zombie = Cast<AZombieCharacter>(Controller->GetPawn());

    if (Zombie == nullptr || PlayerPawn == nullptr) return;

    float DistanceToPlayer = FVector::Distance(Zombie->GetActorLocation(), PlayerPawn->GetActorLocation());

    if (Controller->LineOfSightTo(PlayerPawn) && DistanceToPlayer <= Zombie->SightRange)
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}