#include "BTTask_ChangeToIdleState.h"
#include "ZombieCharacter.h"
#include "ZombieAIController.h"

UBTTask_ChangeToIdleState::UBTTask_ChangeToIdleState()
{
    NodeName = TEXT("ChangeToIdleState");
}

EBTNodeResult::Type UBTTask_ChangeToIdleState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AZombieAIController* ZombieController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
    if (ZombieController == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AZombieCharacter* Zombie = Cast<AZombieCharacter>(ZombieController->GetPawn());

    Zombie->SetIdleState(true);

    return EBTNodeResult::Succeeded;
}