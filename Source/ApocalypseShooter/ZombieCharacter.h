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

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float AttackRange = 140;

};
