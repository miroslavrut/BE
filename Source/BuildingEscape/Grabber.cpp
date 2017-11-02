// Copyright Miroslav Rutesic 2017

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#define OUT

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
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));

	///Look for atached PhysicsHandle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		// Physics handle is found
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("%s missing physics handle component"),*GetOwner()->GetName())
	}

	///Look for atached InputCOmponent (only apears in runtime)
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input Component Found!"))
			InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics input component"), *GetOwner()->GetName())
	}
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed!"))

}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// Get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	// Log out to test
/*	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"),
		*PlayerViewPointLocation.ToString(),
		*PlayerViewPointRotation.ToString()
	) */


	FVector LineTraceEnd =PlayerViewPointLocation + PlayerViewPointRotation.Vector() *Reach;

	/// Draw a red trace in the world to visualize
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);

	/// Setup query paramaters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Ray-cast out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
		);

	/// See what what we hit
	if(Hit.GetActor())
	{
		UE_LOG(LogTemp,Warning,TEXT("%s"),*Hit.GetActor()->GetName())
	}
}

