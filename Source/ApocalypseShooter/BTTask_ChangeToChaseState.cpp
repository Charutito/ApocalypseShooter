#include "BTTask_ChangeToChaseState.h"
#include "ZombieCharacter.h"
#include "ZombieAIController.h"

UBTTask_ChangeToChaseState::UBTTask_ChangeToChaseState()
{
    NodeName = TEXT("ChangeToChaseState");
}

EBTNodeResult::Type UBTTask_ChangeToChaseState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AZombieAIController* ZombieController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
    if (ZombieController == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AZombieCharacter* Zombie = Cast<AZombieCharacter>(ZombieController->GetPawn());

    Zombie->SetChasingState(true);

    return EBTNodeResult::Succeeded;
}