#pragma once

#include "CoreMinimal.h"
#include "PickupableObject.h"
#include "PickupableBullet.generated.h"

UCLASS()
class APOCALYPSESHOOTER_API APickupableBullet : public APickupableObject
{
	GENERATED_BODY()
	
public:
	void OnInteract(AActor* ActorToInteract) override;

private:
	UPROPERTY(EditAnywhere)
	float BulletQtyPack = 20;
};
