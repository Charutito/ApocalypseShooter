#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupableObject.generated.h"

UCLASS()
class APOCALYPSESHOOTER_API APickupableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	APickupableObject();

protected:
	virtual void BeginPlay() override;
	virtual void Show(bool isVisible);

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	FRotator RotationRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	UTexture2D* Image;

	virtual void OnInteract(AActor* ActorToInteract);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
