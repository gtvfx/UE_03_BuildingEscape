// Copyright Gavyn Thompson 2016

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	

	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

    UPROPERTY(BluePrintAssignable)
    FDoorEvent OnOpen;

    UPROPERTY(BluePrintAssignable)
    FDoorEvent OnClose;

private:
	
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate = nullptr;

    UPROPERTY(EditAnywhere)
    float TriggerMass = 40.f;

    // Owning door
    AActor* Owner = nullptr;

    float GetTotalMassOfAcotorsOnPlate();
};
