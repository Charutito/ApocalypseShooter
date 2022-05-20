#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "ShooterAIController.h"
#include "ShooterCharacter.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
	CurrentBulletsQTy = MaxBulletsQty;
}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::HasAmmo()
{
	return CurrentBulletsQTy > 0;
}

void AGun::PullTrigger()
{
	if (!HasAmmo())
	{
		UGameplayStatics::SpawnSoundAttached(GunTriggerFailSound, Mesh, TEXT("ShotgunFlashSocket"));
		return;
	}

	UGameplayStatics::SpawnEmitterAttached(ShotgunFlash, Mesh, TEXT("ShotgunFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(ShotgunSound, Mesh, TEXT("ShotgunFlashSocket"));

	CurrentBulletsQTy--;

	FHitResult Hit;
	FVector ShotDirection;
	if (GunTrace(Hit, ShotDirection))
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);

			APawn* Pawn = Cast<APawn>(HitActor);


			if (Pawn != NULL)
			{
				if ((Pawn->Controller != NULL))
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BloodHit, Hit.Location, ShotDirection.Rotation());
					UGameplayStatics::PlaySoundAtLocation(this, ShotgunBodyImpactSound, Hit.Location);
				}
			}
			else
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShotgunHit, Hit.Location, ShotDirection.Rotation());
				UGameplayStatics::PlaySoundAtLocation(this, ShotgunImpactSound, Hit.Location);
			}
		}
	}
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	FRotator Rotation;
	FVector Location;
	GetOwnerController()->GetPlayerViewPoint(Location, Rotation);

	ShotDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;

	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return nullptr;
	
	return OwnerController;
}

void AGun::LoadBullets(float bulletQty)
{
	CurrentBulletsQTy += bulletQty;
	CurrentBulletsQTy = FMath::Clamp(CurrentBulletsQTy, 0.0f, MaxBulletsQty);

	FString ammoQty = FString::Printf(TEXT("Qty of ammo: %f"), CurrentBulletsQTy);
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Green, ammoQty);
}

float AGun::GetCurrentAmmo()
{
	return CurrentBulletsQTy;
}

float AGun::GetMaxAmmo()
{
	return MaxBulletsQty;
}

void AGun::Show(bool isVisible)
{
	SetActorTickEnabled(isVisible);
	Mesh->SetVisibility(isVisible);
}