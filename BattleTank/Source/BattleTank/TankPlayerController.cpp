// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Public/Tank.h"
#include "Classes/Camera/PlayerCameraManager.h"
#include "GameFramework/Actor.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player is not possessing a tank!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Controller possessing %s"), *(ControlledTank->GetName()));
    }
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return; }
    
    FVector HitLocation; // Out parameter
    if (GetSightRayHitLocation(HitLocation))
    {
        GetControlledTank()->AimAt(HitLocation);
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
        if (GetLookVectorHitLocation(LookDirection, HitLocation))
        {
            //UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
        }

    }

    return true;
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


