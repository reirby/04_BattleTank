// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT(" %s AKU:Tank_C++ construct"), *TankName);
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();	
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT(" %s AKU:Tank_C++ begin play"), *TankName);
}


void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return;}
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (isReloaded) {

		// spawn a projectile at the soket location
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();

	}
}
