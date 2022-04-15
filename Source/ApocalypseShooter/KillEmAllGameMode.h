#pragma once

#include "CoreMinimal.h"
#include "ApocalypseShooterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class APOCALYPSESHOOTER_API AKillEmAllGameMode : public AApocalypseShooterGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled) override;
	
};
