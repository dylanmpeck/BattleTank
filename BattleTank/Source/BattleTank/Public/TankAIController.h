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
    
private:
    // how close can the AI tank get to the player
    float AcceptanceRadius = 3000;
    
    UTankAimingComponent* AimingComponent = nullptr;
    
};
