#include "BTTask_FinishAttack.h"
#include "ZombieCharacter.h"
#include "ZombieAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FinishAttack::UBTTask_FinishAttack()
{
    NodeName = TEXT("Finish Attack");
}

EBTNodeResult::Type UBTTask_FinishAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AZombieAIController* ZombieController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
    if (ZombieController == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AZombieCharacter* Zombie = Cast<AZombieCharacter>(ZombieController->GetPawn());

    OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("CanAttack"), false);
    Zombie->IsAttacking = false;;

    return EBTNodeResult::Succeeded;
}