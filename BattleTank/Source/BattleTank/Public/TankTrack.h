// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
UCLASS( meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintCallable, Category = "Input")
    void SetThrottle(float Throttle);
    
    // Max Force per track in newtons
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 40000000; // assume 40 ton tank and 1g acceleration
    
    void ApplySidewaysForce();
	
protected:
    virtual void BeginPlay() override;
    
private:
    UTankTrack();
    
    void DriveTrack();
    
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& hit);
	
    float CurrentThrottle = 0;
};
