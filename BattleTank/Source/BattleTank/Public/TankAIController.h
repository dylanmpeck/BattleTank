// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

class ATank; // Forward Declaration

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
    void BeginPlay() override;
    
    virtual void Tick(float DeltaTime) override;
    
    UFUNCTION()
    void OnTankDeath();
protected:
    // how close can the AI tank get to the player
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float AcceptanceRadius = 8000;
    
private:
    UTankAimingComponent* AimingComponent = nullptr;
    
    virtual void SetPawn(APawn* InPawn) override;
    
};
