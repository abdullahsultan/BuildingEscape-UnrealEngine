// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "DoorRotation.generated.h" //Always Kepp this file at end


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UDoorRotation : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorRotation();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void DoorOpen(float DeltaTime);
	void DoorClose(float DeltaTime);
	float StartingYaw;
	float OpenYaw;
	float CloseYaw;

private:
	AActor* Player;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;
		
};
