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
	GetPhysicsHandle();
	OnKeyPressORRelease();
}




// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	GetPhysicsBodyInReach();
}


FHitResult UGrabber::GetPhysicsBodyInReach()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	FVector LineEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * 100.0f;

	FHitResult Hit = FHitResult();
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerViewPointLocation,
		LineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);


	if (Hit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Hit.GetActor()->GetName());
	}

	return Hit;
}

void UGrabber::GetPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		//
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Physics Hndler not found."));
	}
}

void UGrabber::OnKeyPressORRelease()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (Input)
	{
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input Controller not found."));
	}
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Input Is Working"));
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Key Released"));
}

