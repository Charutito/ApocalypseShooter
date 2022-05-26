#include "BTTask_ChangeToWalkingState.h"
#include "ZombieCharacter.h"
#include "ZombieAIController.h"

UBTTask_ChangeToWalkingState::UBTTask_ChangeToWalkingState()
{
	NodeName = TEXT("ChangeToWalkingState");
}

EBTNodeResult::Type UBTTask_ChangeToWalkingState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AZombieAIController* ZombieController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
    if (ZombieController == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AZombieCharacter* Zombie = Cast<AZombieCharacter>(ZombieController->GetPawn());

    Zombie->SetChasingState(false);
    Zombie->SetIdleState(false);

    return EBTNodeResult::Succeeded;
}