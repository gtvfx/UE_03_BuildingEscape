// Copyright Gavyn Thompson 2016

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

    FindPhysicsHandleComponent();

    SetUpInputComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{
    /// Look for attached physics handle
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle)
    {
        UE_LOG(LogTemp, Warning, TEXT("PhysicsHandle found on %s!"), *GetOwner()->GetName())
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("PhysicsHandle not found on %s!"), *GetOwner()->GetName());
    }
}

void UGrabber::SetUpInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("InputComponent found on %s!"), *GetOwner()->GetName());

        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);

        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("InputComponent not found on %s!"), *GetOwner()->GetName());
    }
}

void UGrabber::Grab()
{
    UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));

    // LineTrace and see if we reach any Actors with Physics Body Collision channel set
    GetFirstPhysicsBodyInReach();

    // If we hit something then attach a physics handle
    // TODO attach physics handle
}

void UGrabber::Release()
{
    UE_LOG(LogTemp, Warning, TEXT("Grab Released"));

    // TODO Release Physics handle
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    // If the physics handle is attached
        // move the object that we're holding
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
    // Get player viewpoint
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

    // Log out to test
    // UE_LOG(LogTemp, Warning, TEXT("Location: %s | Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

    // Draw a trace line
    FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

    /// DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

    /// Setup Query parameters
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

    /// Line-Trace/Ray-cast out to reach distance
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(
        OUT Hit,
        PlayerViewPointLocation,
        LineTraceEnd,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParameters
    );

    /// See what we hit
    AActor* ActorHit = Hit.GetActor();
    if (ActorHit)
    {
        UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
    }

    return FHitResult();
}
