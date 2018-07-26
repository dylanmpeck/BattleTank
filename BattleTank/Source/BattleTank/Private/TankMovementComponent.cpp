// Copyright Dylan Peck

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }
    LeftTrack = LeftTrackToSet;
    RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    if (!ensure(LeftTrack && RightTrack)) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    if (!ensure(LeftTrack && RightTrack)) { return; }
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    
    float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
    FVector RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention);
    
    IntendMoveForward(ForwardThrow);
    IntendTurnRight(RightThrow.Z);
}



