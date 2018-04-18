// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "BattleTank.h"


void UTankBarrel::Elevate(float DegreesPerSecond)
{
	// move the barrel to the right ammount this frame
	// given the max elevation speed and the frame time 
	UE_LOG(LogTemp, Warning, TEXT("Barrel-Elevate() called at speen %f"), DegreesPerSecond);
}

