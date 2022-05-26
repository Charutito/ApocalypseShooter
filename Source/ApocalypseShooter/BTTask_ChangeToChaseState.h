#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChangeToChaseState.generated.h"

UCLASS()
class APOCALYPSESHOOTER_API UBTTask_ChangeToChaseState : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_ChangeToChaseState();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
