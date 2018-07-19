// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"

void UTurret::Rotate(float RelativeSpeed)
{
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
    
    auto RotationChange = RelativeSpeed * TurretRotationSpeed * GetWorld()->DeltaTimeSeconds;
    auto Rotation = RelativeRotation.Yaw + RotationChange;
    
    SetRelativeRotation(FRotator(0, Rotation, 0));
}


