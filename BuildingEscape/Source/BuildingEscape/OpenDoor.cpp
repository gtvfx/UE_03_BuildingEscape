// Copyright Gavyn Thompson 2016

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

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

    Owner = GetOwner();

    if (!PressurePlate)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing Pressure Plate"), *GetOwner()->GetName());
    }

    //PressureTrigger = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
    Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
    Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    if (GetTotalMassOfAcotorsOnPlate() > TriggerMass)
    {
        OpenDoor();
        DoorLastOpenTime = GetWorld()->GetTimeSeconds();
    }


    // Check if it's time to close the door
    if (GetWorld()->GetTimeSeconds() - DoorLastOpenTime > DoorCloseDelay)
    {
        CloseDoor();
    }
}

float UOpenDoor::GetTotalMassOfAcotorsOnPlate()
{
    float TotalMass = 0.f;

    // Find overlapping Actors
    TArray<AActor*> OverlappingActors;

    if (!PressurePlate) { return TotalMass; }
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);

    // Iterate through them adding up their mass
    for (const auto& Actor : OverlappingActors)
    {
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

        UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName());
    }


    return TotalMass;
}

