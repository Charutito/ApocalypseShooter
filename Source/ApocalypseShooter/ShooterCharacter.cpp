#include "ShooterCharacter.h"
#include "Gun.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = DefaultFOV;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraBoom);
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);

	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
}

void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckCameraZoom(DeltaTime);
}

void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);


	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::PerformShoot);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Pressed, this, &AShooterCharacter::PressAim);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Released, this, &AShooterCharacter::ReleaseAim);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &AShooterCharacter::PressSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &AShooterCharacter::ReleaseSprint);
}

float AShooterCharacter::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::PerformShoot()
{
	if (!isSprinting)
	{
		Gun->PullTrigger();
	}
}

void AShooterCharacter::PressAim()
{
	isSprinting = false;
	isZooming = true;
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * SpeedAimFactor;
}

void AShooterCharacter::ReleaseAim()
{
	isZooming = false;
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
}

void AShooterCharacter::CheckCameraZoom(float DeltaTime)
{
	float TargetFOV = isZooming ? ZoomedFOV : DefaultFOV;

	if (CameraBoom->TargetArmLength != TargetFOV)
	{
		float NewFOV = FMath::FInterpTo(CameraBoom->TargetArmLength, TargetFOV, DeltaTime, ZoomInterpSpeed);
		CameraBoom->TargetArmLength = NewFOV;
	}
}

void AShooterCharacter::PressSprint()
{
	if (!isZooming)
	{
		isSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * SpeedSprintFactor;
	}
}

void AShooterCharacter::ReleaseSprint()
{
	isSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
}