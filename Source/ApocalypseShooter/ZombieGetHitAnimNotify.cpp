#include "ZombieGetHitAnimNotify.h"
#include "ZombieCharacter.h"

void UZombieGetHitAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
    {
        AZombieCharacter* Zombie = Cast<AZombieCharacter>(MeshComp->GetOwner());

        if (Zombie != nullptr)
        {
            Zombie->GetHit(false);
        }
    }
}