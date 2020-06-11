// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	UE_LOG(LogTemp, Warning, TEXT("Location =%s	.... Rotation = %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.Vector().ToString());

	FVector LineEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * 100.0f;
		FVector(0.0f, 0.0f, 50.0f);
	DrawDebugLine(GetWorld(),PlayerViewPointLocation, LineEnd, FColor(0,255,0), false, 0.0f, 0.0f, 10.0f);
}

