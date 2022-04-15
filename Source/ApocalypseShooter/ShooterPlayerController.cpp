#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    CurrentDelay = RestartDelay;

    UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
    if (LoseScreen != nullptr)
    {
        LoseScreen->AddToViewport();
    }

    FTimerHandle DelayCountDownTimer;
    GetWorldTimerManager().SetTimer(DelayCountDownTimer, this, &AShooterPlayerController::RestartCountDown, 1.f, true, 0.0);
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::RestartCountDown()
{
    if (CurrentDelay != 0)
    {
        CurrentDelay = CurrentDelay - 1;
    }
}
