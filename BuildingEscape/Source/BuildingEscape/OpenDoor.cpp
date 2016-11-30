// Copyright Gavyn Thompson 2016

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

    PressureTrigger = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
    // Find the owning Actor
    AActor* Owner = GetOwner();

    // Create rotator
    FRotator NewRotation = FRotator(0.0f, -60.0f, 0.0f);

    // Set the door rotation
    Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the TriggerVolume

    // if the PressureTrigger is in the volume
    if (PressurePlate->IsOverlappingActor(PressureTrigger))
    {
        // then open door
        OpenDoor();
    }
}

