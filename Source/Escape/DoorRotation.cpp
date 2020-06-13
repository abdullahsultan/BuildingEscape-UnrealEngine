// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorRotation.h"
#include "Sound/AmbientSound.h"
#include "Kismet/GameplayStatics.h"
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
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetName());
	if (GetTotalMassOnPressurePlate() >= 40.0f)
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

float UDoorRotation::GetTotalMassOnPressurePlate()
{
	TArray<AActor*> ActorsOnPressurePlate;
	PressurePlate->GetOverlappingActors(ActorsOnPressurePlate);
	float TotalMass= 0.0f;
	//AActor* Actor;
	for(AActor* Actor: ActorsOnPressurePlate)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

