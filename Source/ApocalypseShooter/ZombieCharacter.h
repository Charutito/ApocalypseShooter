#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameFramework/Character.h"
#include "ZombieCharacter.generated.h"

UCLASS()
class APOCALYPSESHOOTER_API AZombieCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AZombieCharacter();
	virtual void Tick(float DeltaTime) override;
	void Attack();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsAttacking;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float AttackRange = 140;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> DamageFloatingText;

	UPROPERTY(EditAnywhere)
	float DamageTextPositionOffset = 0.f;
};
