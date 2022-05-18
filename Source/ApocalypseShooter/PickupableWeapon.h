#pragma once

#include "CoreMinimal.h"
#include "PickupableObject.h"
#include "PickupableWeapon.generated.h"

class AGun;

UCLASS()
class APOCALYPSESHOOTER_API APickupableWeapon : public APickupableObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

};
