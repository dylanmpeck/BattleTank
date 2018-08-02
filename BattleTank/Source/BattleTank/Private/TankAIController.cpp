// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
// Depends on movement component via pathfinding systems.

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    auto PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
    if (!PlayerTank || !GetPawn()) { return; }
    
    AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    
    MoveToActor(PlayerTank, AcceptanceRadius);
    
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    
    if (AimingComponent->GetFiringState() == EFiringState::Locked)
    {
        AimingComponent->Fire();
    }

}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    
    if (InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!ensure(PossessedTank)) { return; }
        
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
    }
}

void ATankAIController::OnTankDeath()
{
    UE_LOG(LogTemp, Warning, TEXT("AI Tank is Dead"));
    
    if (!GetPawn()) { return; }
    GetPawn()->DetachFromControllerPendingDestroy();
}



