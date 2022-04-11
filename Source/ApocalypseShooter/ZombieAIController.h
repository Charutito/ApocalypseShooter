#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class APOCALYPSESHOOTER_API AZombieAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime);
	void MoveToPlayerIfInSight();

protected:
	virtual void BeginPlay() override;

private:
	APawn* PlayerPawn;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehaviour;
	
};
