#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class APOCALYPSESHOOTER_API AShooterAIController : public AAIController
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

	UPROPERTY(EditAnywhere)
	FVector FirstLocation = FVector(900, -1411, 88);

	UPROPERTY(EditAnywhere)
	FVector SecondLocation = FVector(-250, -1411, 88);
};
