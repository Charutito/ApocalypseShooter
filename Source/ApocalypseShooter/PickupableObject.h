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

	virtual void OnInteract();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
