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

	FVector HitLocation; // out parameter
	if (GetSightRayHitLocation(HitLocation)) // has a side efect, is going to line trace
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s "), *(HitLocation.ToString()));
		
		GetControlledTank()->AimAt(HitLocation);
	}
	
}

// Get world location if linetrace though crosshair. if it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto Screenlocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
	
	//de project the screen position to a world direction
	FVector LookDirection;
	if (GetLookDirection(Screenlocation, LookDirection))
	{
		// line trace alonng that LookDirection and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D Screenlocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // to be descadrded
	DeprojectScreenPositionToWorld	(Screenlocation.X,Screenlocation.Y,CameraWorldLocation,LookDirection);
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StarLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StarLocation + LookDirection*LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StarLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
	
}