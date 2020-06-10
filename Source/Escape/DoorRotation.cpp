// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorRotation.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UDoorRotation::UDoorRotation()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorRotation::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CloseYaw = GetOwner()->GetActorRotation().Yaw;
	OpenYaw = GetOwner()->GetActorRotation().Yaw + 90.0f;
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


// Called every frame
void UDoorRotation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (PressurePlate->IsOverlappingActor(Player))
	{
		DoorOpen(DeltaTime);
	}
	else
	{
		DoorClose(DeltaTime);
	}
}

void UDoorRotation::DoorOpen(float DeltaTime)
{
	StartingYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator Rotator = FRotator(0.0f, StartingYaw, 0.0f);
	Rotator.Yaw = FMath::Lerp(StartingYaw, OpenYaw, 0.85f * DeltaTime);
	GetOwner()->SetActorRotation(Rotator);
}

void UDoorRotation::DoorClose(float DeltaTime)
{
	StartingYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator Rotator = FRotator(0.0f, StartingYaw, 0.0f);
	Rotator.Yaw = FMath::Lerp(StartingYaw, CloseYaw, 0.85f * DeltaTime);
	GetOwner()->SetActorRotation(Rotator);
}

