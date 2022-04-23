#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class APOCALYPSESHOOTER_API AShooterCharacter : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:	
	AShooterCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement", Meta = (BlueprintProtected = "true"))
	float SpeedSprintFactor = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement", Meta = (BlueprintProtected = "true"))
	float SpeedAimFactor = 0.75;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement", Meta = (BlueprintProtected = "true"))
	float BaseSpeed;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void PerformShoot();
	void PressAim();
	void ReleaseAim();
	void CheckCameraZoom(float DeltaTime);
	void PressSprint();
	void ReleaseSprint();

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float DefaultFOV = 300;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float ZoomedFOV = 80;

	UPROPERTY(EditDefaultsOnly, Category = "Camera", meta = (ClampMin = 0.1, ClampMax = 100))
	float ZoomInterpSpeed;
	
	bool isZooming;
	bool isSprinting;

	UPROPERTY(EditDefaultsOnly)
	float RotationRate = 10;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;
};
