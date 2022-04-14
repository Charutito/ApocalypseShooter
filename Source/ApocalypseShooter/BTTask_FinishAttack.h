#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FinishAttack.generated.h"

/**
 * 
 */
UCLASS()
class APOCALYPSESHOOTER_API UBTTask_FinishAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_FinishAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
