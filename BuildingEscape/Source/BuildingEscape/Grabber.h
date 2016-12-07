// Copyright Gavyn Thompson 2016

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:

    float Reach = 100.f;
	
    UPhysicsHandleComponent* PhysicsHandle = nullptr;
    UInputComponent* InputComponent = nullptr;

    // Raycast and grab the Actor in reach
    void Grab();

    // Called when Grab is released
    void Release();

    void FindPhysicsHandleComponent();
    void SetUpInputComponent();

    // Return hit for first physics body in reach
    const FHitResult GetFirstPhysicsBodyInReach();
};
