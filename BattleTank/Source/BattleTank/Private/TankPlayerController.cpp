// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Classes/Camera/PlayerCameraManager.h"
#include "Public/TankAimingComponent.h"
#include "GameFramework/Actor.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    
    if (!ensure(AimingComponent)) { return; }
    FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetPawn()) { return; }
    if (!ensure(AimingComponent)) { return; }
    
    FVector HitLocation; // Out parameter
    bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
    if (bGotHitLocation)
    {
        AimingComponent->AimAt(HitLocation);
    }
    
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    // Find the crosshair position
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    FVector2D ScreenLocation((CrosshairXLocation * ViewportSizeX), (CrosshairYLocation * ViewportSizeY));
    
    // De project screen position of cross hair to world location
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        return GetLookVectorHitLocation(LookDirection, HitLocation);
    }
    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector WorldLocation; // for discarding
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FVector Start = PlayerCameraManager->GetCameraLocation();
    FVector End = Start + (LookDirection * LineTraceRange);
    FHitResult Hit;
    if (GetWorld()->LineTraceSingleByChannel
    (
     Hit,
     Start,
     End,
     ECollisionChannel::ECC_Visibility
    ))
    {
        HitLocation = Hit.Location;
        return true;
    }
    HitLocation = FVector(0);
    return false;
}


