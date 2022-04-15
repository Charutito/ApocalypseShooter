#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class APOCALYPSESHOOTER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;
	UPROPERTY(VisibleAnywhere)
	float CurrentHealth = 10;

private:
	void NotifyDeadToGameMode();

};
