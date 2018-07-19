// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "Public/Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto PLayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	
	if (PLayerTank)
	{
		//move towards the player
		MoveToActor(PLayerTank, AcceptanceRadius);

		//aim at the player
		ControlledTank->AimAt(PLayerTank->GetActorLocation());
	
		ControlledTank->Fire(); 
	}
	

}


