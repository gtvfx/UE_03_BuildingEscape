// Copyright Gavyn Thompson 2016

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	

	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

    void OpenDoor();
    void CloseDoor();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
    UPROPERTY(EditAnywhere)
    float OpenAngle = -90.0f;
	
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate;

    UPROPERTY(EditAnywhere)
    float DoorCloseDelay = 0.1f;

    float DoorLastOpenTime;

    float TriggerMass = 40.f;
    
    // AActor* PressureTrigger; // Remember Pawn inherits from Actor
    AActor* Owner; // Owning door

    float GetTotalMassOfAcotorsOnPlate();
};
