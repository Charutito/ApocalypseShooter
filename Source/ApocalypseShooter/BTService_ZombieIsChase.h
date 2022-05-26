#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_ZombieIsChase.generated.h"

UCLASS()
class APOCALYPSESHOOTER_API UBTService_ZombieIsChase : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_ZombieIsChase();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
