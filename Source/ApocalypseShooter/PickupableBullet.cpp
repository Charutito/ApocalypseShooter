#include "PickupableBullet.h"
#include "ShooterCharacter.h"


void APickupableBullet::OnInteract(AActor* ActorToInteract)
{
	AShooterCharacter* Character = Cast<AShooterCharacter>(ActorToInteract);

	if (Character != nullptr)
	{
		if (Character->GetGunCurrentAmmo() == Character->GetGunMaxAmmo())
		{
			return;
		}

		FString pickup = FString::Printf(TEXT("Picked up: %s"), *Name);
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, pickup);

		Show(false);
		Character->ReloadGun(BulletQtyPack);
	}
}