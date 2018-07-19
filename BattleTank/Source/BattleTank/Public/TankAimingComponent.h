// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Forward Declaration
class UTankBarrel;
class UTurret;

//Holds barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:
    
    void AimAt(FVector HitLocation, float LaunchSpeed);
    
    void SetBarrelReference(UTankBarrel* BarrelToSet);
    
    void SetTurretReference(UTurret* BarrelToSet);
    
private:
    UTankBarrel* Barrel = nullptr;
    
    UTurret* Turret = nullptr;

    void MoveBarrelTowards(FVector AimDirection);
};
