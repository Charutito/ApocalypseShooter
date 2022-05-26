#include "BTService_ZombieIsChase.h"
#include "ZombieCharacter.h"
#include "ZombieAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_ZombieIsChase::UBTService_ZombieIsChase()
{
	NodeName = TEXT("Zombie Is Chase");
}

void UBTService_ZombieIsChase::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AZombieAIController* ZombieController = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
    if (ZombieController == nullptr)
    {
        return;
    }

    AZombieCharacter* Zombie = Cast<AZombieCharacter>(ZombieController->GetPawn());

    OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), Zombie->IsChasing);

}