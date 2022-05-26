#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChangeToWalkingState.generated.h"

UCLASS()
class APOCALYPSESHOOTER_API UBTTask_ChangeToWalkingState : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_ChangeToWalkingState();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
