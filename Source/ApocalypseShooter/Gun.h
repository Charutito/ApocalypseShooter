#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class APOCALYPSESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	AGun();
	void PullTrigger();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ShotgunFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ShotgunHit;

	UPROPERTY(EditAnywhere)
	UParticleSystem* BloodHit;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere)
	float Damage = 10;
};
