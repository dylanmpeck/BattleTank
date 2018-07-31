// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Turret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
    Super::BeginPlay();
    // so that first fire is after initial reload
    LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if (RoundsLeft <= 0)
    {
        FiringState = EFiringState::OutOfAmmo;
    }
    else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
    {
        FiringState = EFiringState::Reloading;
    }
    else if (BarrelIsMoving())
    {
        FiringState = EFiringState::Aiming;
    }
    else
    {
        FiringState = EFiringState::Locked;
    }
}

EFiringState UTankAimingComponent::GetFiringState() const
{
    return FiringState;
}

bool UTankAimingComponent::BarrelIsMoving()
{
    if (!ensure(Barrel)) { return false; }
    
    FVector BarrelForwardVector = Barrel->GetForwardVector();
    if (!(BarrelForwardVector.Equals(AimDirection, 0.01f)))
    {
        return true;
    }
    return false;
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTurret* TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
    if (ensure(Barrel))
    {
        FVector OutLaunchVelocity;
        FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
        
        bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
        (
            this,
            OutLaunchVelocity,
            StartLocation,
            HitLocation,
            LaunchSpeed,
            false,
            0,
            0,
            ESuggestProjVelocityTraceOption::DoNotTrace
         );
        if (bHaveAimSolution)
        {
            AimDirection = OutLaunchVelocity.GetSafeNormal();
            MoveBarrelTowards();
            
            auto Time = GetWorld()->GetTimeSeconds();
            //UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), Time);
        }
        else
        {
            auto Time = GetWorld()->GetTimeSeconds();
            //UE_LOG(LogTemp, Warning, TEXT("%f: No solution found"), Time);
        }
    }
}

void UTankAimingComponent::MoveBarrelTowards()
{
    if (!ensure(Barrel) || !ensure(Turret)) { return; }
    
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    
    Barrel->Elevate(DeltaRotator.Pitch);
    if (DeltaRotator.Yaw > 180.0f)
    {
        DeltaRotator.Yaw = DeltaRotator.Yaw - 180.0f;
        Turret->Rotate(DeltaRotator.Yaw * -1);
    }
    else if (DeltaRotator.Yaw < -180.0f)
    {
        DeltaRotator.Yaw = DeltaRotator.Yaw + 180.0f;
        Turret->Rotate(DeltaRotator.Yaw * -1);
    }
    else
    {
        Turret->Rotate(DeltaRotator.Yaw);
    }

}

void UTankAimingComponent::Fire()
{
    if (!ProjectileBlueprint)
    {
        UE_LOG(LogTemp, Warning, TEXT("No Projectile Blueprint Found!"));
        return;
    }
    
    if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
    {
        if (!ensure(Barrel)) { return; }
        if (!ensure(ProjectileBlueprint)) { return; }
        // spawn a projectile at barrel location
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
            ProjectileBlueprint,
            Barrel->GetSocketLocation(FName("Projectile")),
            Barrel->GetSocketRotation(FName("Projectile")),
            SpawnInfo
            );
        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = GetWorld()->GetTimeSeconds();
        RoundsLeft--;
    }
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
    return RoundsLeft;
}
