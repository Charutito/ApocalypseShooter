#include "Components/BoxComponent.h"
#include "PickupableObject.h"

APickupableObject::APickupableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	this->RootComponent = SceneComponent;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);

	RotationRate = FRotator(0.0f, 180.0f, 0.0f);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetGenerateOverlapEvents(true);
	BoxCollider->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &APickupableObject::OnOverlapBegin);
	BoxCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

}

void APickupableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickupableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(RotationRate * DeltaTime);
}

void APickupableObject::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		FString pickup = FString::Printf(TEXT("Picked up: %s"), *GetName());
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, pickup);

		Destroy();
	}
}
