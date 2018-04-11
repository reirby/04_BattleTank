// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"

	


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
		auto ControlledTank =GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller not posessing a tank"));
	}
	else { UE_LOG(LogTemp, Warning, TEXT("Player Controller possessing: %s "), *(ControlledTank->GetName()));
	}
}


// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector OutHitLocation; // out parameter
	if (GetSightRayHitLocation(OutHitLocation)) // has a side efect, is going to line trace
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s "), *(OutHitLocation.ToString()));
		
		// TODO tell controlled tank to aim at this point
	}
	
}

// Get world location if linetrace though crosshair. if it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.0);
	return true;
}