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
    if (PhysicsHandle == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("PhysicsHandle not found on %s!"), *GetOwner()->GetName());
    }
}

void UGrabber::SetUpInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
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
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent(); // Gets the mesh in this case
    auto ActorHit = HitResult.GetActor();

    /// if we hit something then attach a physics handle
    if (ActorHit)
    { // NAME_None is telling it that no bones are needed
        PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
    }
}

void UGrabber::Release()
{
    PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    // If the physics handle is attached
    if (PhysicsHandle->GrabbedComponent)
    {
        // move the object that we're holding
        PhysicsHandle->SetTargetLocation(GetReachLineEnd());
    }
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
    /// Setup Query parameters
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

    /// Line-Trace/Ray-cast out to reach distance
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByObjectType(
        OUT HitResult,
        GetReachLineStart(),
        GetReachLineEnd(),
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParameters
    );

    return HitResult;
}

FVector UGrabber::GetReachLineStart()
{
    // Get player viewpoint
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

    return PlayerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd()
{
    // Get player viewpoint
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

    return PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
}

