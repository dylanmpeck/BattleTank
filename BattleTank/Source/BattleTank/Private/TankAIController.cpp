// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
// Depends on movement component via pathfinding systems.

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    APawn* PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
    if (!ensure(PlayerTank)) { return; }
    
    AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    
    MoveToActor(PlayerTank, AcceptanceRadius);
    
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    
    AimingComponent->Fire();
}



