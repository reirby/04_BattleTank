// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PLayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	
	if (!ensure(PLayerTank && ControlledTank)) { return; }
	//move towards the player
	MoveToActor(PLayerTank, AcceptanceRadius);

	//aim at the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PLayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::locked)
	{
		AimingComponent->Fire();
	}
}


