// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    ATank* ControlledTank = Cast<ATank>(GetPawn());
    if (!ControlledTank) { return; }
    ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (!PlayerTank) { return; }
    
    ControlledTank->AimAt(PlayerTank->GetActorLocation());
    
    ControlledTank->Fire();
}



