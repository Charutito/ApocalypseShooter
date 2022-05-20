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
	bool HasAmmo();
	void LoadBullets(float bulletQty);
	float GetCurrentAmmo();
	float GetMaxAmmo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	bool IsPistol;

	void Show(bool isVisible);


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
	USoundBase* ShotgunSound;

	UPROPERTY(EditAnywhere)
	USoundBase* ShotgunImpactSound;

	UPROPERTY(EditAnywhere)
	USoundBase* ShotgunBodyImpactSound;

	UPROPERTY(EditAnywhere)
	USoundBase* GunTriggerFailSound;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	UPROPERTY(EditAnywhere)
	float MaxBulletsQty = 50;

	float CurrentBulletsQTy;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);
	AController* GetOwnerController() const;
};
