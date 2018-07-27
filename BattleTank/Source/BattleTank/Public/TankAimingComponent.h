// Copyright Dylan Peck.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
    Reloading,
    Aiming,
    Locked,
    OutOfAmmo
};

//Forward Declaration
class UTankBarrel;
class UTurret;
class AProjectile;

//Holds barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialize(UTankBarrel* BarrelToSet, UTurret* TurretToSet);
    
    void AimAt(FVector HitLocation);
    
    EFiringState GetFiringState() const;
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    int GetRoundsLeft() const;
    
    UFUNCTION(BlueprintCallable, Category = "Input")
    void Fire();
    
    UTankBarrel* Barrel = nullptr;
    UTurret* Turret = nullptr;
    
protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Reloading;
    
    virtual void BeginPlay() override;
    
    bool BarrelIsMoving();
    
private:
    // Sets default values for this component's properties
    UTankAimingComponent();
    
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float ReloadTimeInSeconds = 3;
    
    float LastFireTime = 0;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 4000;
    
    int RoundsLeft = 3;

    void MoveBarrelTowards();
    
    FVector AimDirection;
};
