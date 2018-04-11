// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	
	ATank* GetControlledTank() const;

	

private:
	// Move the barrel to hit  where the crosshair intersects the world
	void AimTowardsCrosshair();
	// return an OUT parameter/ true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
};

