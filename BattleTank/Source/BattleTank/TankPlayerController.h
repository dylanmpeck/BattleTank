// Copyright Dylan Peck.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    void BeginPlay() override;
	
    void Tick(float DeltaTime) override;
    
protected:
    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimingCompRef);
    
private:
    void AimTowardsCrosshair();
    
    bool GetSightRayHitLocation(FVector& HitLocation) const;
    
    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
    
    bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
    
    UPROPERTY(EditDefaultsOnly)
    float CrosshairXLocation = 0.5;
    
    UPROPERTY(EditDefaultsOnly)
    float CrosshairYLocation = 0.3333;
    
    int64 LineTraceRange = 1000000;
    
    UTankAimingComponent* AimingComponent = nullptr;
};
