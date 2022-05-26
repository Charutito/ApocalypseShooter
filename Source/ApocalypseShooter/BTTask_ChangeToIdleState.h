#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChangeToIdleState.generated.h"

UCLASS()
class APOCALYPSESHOOTER_API UBTTask_ChangeToIdleState : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ChangeToIdleState();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
