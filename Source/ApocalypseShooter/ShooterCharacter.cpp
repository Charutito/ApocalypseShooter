#include "ShooterCharacter.h"
#include "Gun.h"
#include "PickupableObject.h"
#include "PickupableWeapon.h"
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
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
}

void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckCameraZoom(DeltaTime);
	
	ElapsedShootTime += DeltaTime;
	if (ElapsedShootTime >= GetShootInterval())
	{
		PerformShoot();
		ElapsedShootTime = 0.f;
	}
	
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
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::StartShootState);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Released, this, &AShooterCharacter::EndShootState);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Pressed, this, &AShooterCharacter::PressAim);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Released, this, &AShooterCharacter::ReleaseAim);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &AShooterCharacter::PressSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &AShooterCharacter::ReleaseSprint);
	PlayerInputComponent->BindAction(TEXT("Inventory_Slot_1"), EInputEvent::IE_Pressed, this, &AShooterCharacter::GetFirstGun);
	PlayerInputComponent->BindAction(TEXT("Inventory_Slot_2"), EInputEvent::IE_Pressed, this, &AShooterCharacter::GetSecondGun);
	PlayerInputComponent->BindAction(TEXT("Inventory_Slot_3"), EInputEvent::IE_Pressed, this, &AShooterCharacter::GetThirdGun);

	PlayerInputComponent->BindAction(TEXT("ScrollInventoryUp"), EInputEvent::IE_Pressed, this, &AShooterCharacter::OnScrollInventoryUp);
	PlayerInputComponent->BindAction(TEXT("ScrollInventoryDown"), EInputEvent::IE_Pressed, this, &AShooterCharacter::OnScrollInventoryDown);
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

void AShooterCharacter::StartShootState()
{
	ElapsedShootTime = 0.f;

	if (Gun != nullptr && Gun->IsPistol)
	{
		IsShootPreessedDown = true;
		PerformShoot();
		IsShootPreessedDown = false;
		return;
	}

	IsShootPreessedDown = true;
	PerformShoot();
}

void AShooterCharacter::EndShootState()
{
	IsShootPreessedDown = false;
}

void AShooterCharacter::PerformShoot()
{
	if (Gun != nullptr && !isSprinting && IsShootPreessedDown)
	{
		Gun->PullTrigger();
	}
}

float AShooterCharacter::GetShootInterval()
{
	if (Gun != nullptr && !Gun->IsPistol)
	{
		return Gun->ShootInterval;
	}

	return Period;
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

void AShooterCharacter::GetFirstGun()
{
	GetInventoryItemByIndex(0);
}

void AShooterCharacter::GetSecondGun()
{
	GetInventoryItemByIndex(1);
}

void AShooterCharacter::GetThirdGun()
{
	GetInventoryItemByIndex(2);
}

void AShooterCharacter::OnScrollInventoryUp()
{
	FString pickup = FString::Printf(TEXT("Up"));
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, pickup);

	if (Gun == nullptr) return;

	int LastInventoryIndex = InventorySlots.Num() - 1;
	int NextIndex = CurrentInventorySlotIndex + 1;

	if (NextIndex <= LastInventoryIndex)
	{
		GetInventoryItemByIndex(NextIndex);
	}
	else
	{
		GetInventoryItemByIndex(0);
	}
}

void AShooterCharacter::OnScrollInventoryDown()
{
	FString pickup = FString::Printf(TEXT("Down"));
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, pickup);

	if (Gun == nullptr) return;

	int LastInventoryIndex = InventorySlots.Num() - 1;
	int NextIndex = CurrentInventorySlotIndex - 1;

	if (NextIndex < 0)
	{
		GetInventoryItemByIndex(LastInventoryIndex);
	}
	else
	{
		GetInventoryItemByIndex(NextIndex);
	}
	
}

void AShooterCharacter::GetInventoryItemByIndex(int index)
{
	if (index < InventorySlots.Num() && InventorySlots[index] != nullptr)
	{
		SetCurrentGun(InventorySlots[index], index);
	}
}

void AShooterCharacter::AddToInventory(APickupableObject* pickupableObject)
{
	APickupableWeapon* Weapon = Cast<APickupableWeapon>(pickupableObject);

	if (Weapon != nullptr)
	{
		FString pickup = FString::Printf(TEXT("Picked up not NULL: %s"), *Weapon->Name);
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, pickup);
		AGun* PickUpGun = GetWorld()->SpawnActor<AGun>(Weapon->GunClass);
		InventorySlots.Add(PickUpGun);

		if (IsUnarmed())
		{
			SetCurrentGun(PickUpGun, 0);
		}
	}

	UpdateInventory();
}

void AShooterCharacter::UpdateInventory()
{
	OnUpdateInventory.Broadcast(InventorySlots);
}

void AShooterCharacter::ReloadGun(float bulletQty)
{
	if (Gun != nullptr)
	{
		Gun->LoadBullets(bulletQty);
	}
}

float AShooterCharacter::GetGunCurrentAmmo()
{
	if (IsUnarmed())
	{
		return 0;
	}

	return Gun->GetCurrentAmmo();
}

float AShooterCharacter::GetGunMaxAmmo()
{
	if (IsUnarmed())
	{
		return 0;
	}

	return Gun->GetMaxAmmo();
}

float AShooterCharacter::GetGunCurrentDamage()
{
	if (IsUnarmed())
	{
		return 0;
	}

	return  Gun->GetGunCurrentDamage();
}

bool AShooterCharacter::IsUnarmed() const
{
	return Gun == nullptr;
}

void AShooterCharacter::SetCurrentGun(AGun* CurrentGun, int index)
{
	if (Gun != nullptr)
	{
		Gun->Show(false);
		Gun = nullptr;
	}

	CurrentInventorySlotIndex = index;
	Gun = CurrentGun;
	Gun->Show(true);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

bool AShooterCharacter::HasAPistol()
{
	if (Gun != nullptr)
	{
		return Gun->IsPistol;
	}

	return false;
}

int AShooterCharacter::GetCurrentWeaponSlotIndex()
{
	if (Gun != nullptr)
	{
		return CurrentInventorySlotIndex;
	}

	return 0;
}