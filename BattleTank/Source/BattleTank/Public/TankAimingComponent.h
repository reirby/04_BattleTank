// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	reloading,
	aiming,
	locked
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrels properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector Hitlocation);

	UFUNCTION(BlueprintCallable)
	void Fire();


protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::aiming;


private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	void MoveBarrelTowards(FVector AimDirection);

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 5000; 


	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;


	double LastFireTime = 0;
};
