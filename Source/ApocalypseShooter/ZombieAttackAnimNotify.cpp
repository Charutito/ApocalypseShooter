#include "ZombieAttackAnimNotify.h"
#include "Engine.h"
#include "ZombieCharacter.h"

void UZombieAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
    {
        AZombieCharacter* Zombie = Cast<AZombieCharacter>(MeshComp->GetOwner());

        if (Zombie != nullptr)
        {
            Zombie->Attack();
        }
    }
}