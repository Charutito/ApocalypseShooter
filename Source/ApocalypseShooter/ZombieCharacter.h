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
	void SetIdleState(bool isIdle);
	void SetChasingState(bool isChasing);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsIdle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsChasing;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	UPROPERTY(EditAnywhere)
	float AttackRange = 140;

	UPROPERTY(EditAnywhere)
	float SightRange = 300;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float Damage = 10;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> DamageFloatingText;

	UPROPERTY(EditAnywhere)
	float DamageTextPositionOffset = 0.f;
};
