#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class APOCALYPSESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	void RestartCountDown();
	void CreateScreenWidget(TSubclassOf<class UUserWidget> ScreenClass);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RestartDelay = 5;

	UPROPERTY(BlueprintReadOnly)
	float CurrentDelay;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;

	FTimerHandle RestartTimer;
};
