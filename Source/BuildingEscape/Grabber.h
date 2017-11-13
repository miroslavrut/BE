// Copyright Miroslav Rutesic 2017
#pragma once

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// How far ahead of player can we reach
	float Reach = 150.f;

	class UPhysicsHandleComponent* PhysicsHandle = nullptr;
	class UInputComponent* InputComponent = nullptr;       // class added for avoiding errors,forum 83.
	
	// Ray-cast and grab what's in reach
	void Grab();

	// Called when grab is released
	void Release();

	// Find (asumed) atached physics handle
	void FindPhysicsHandleComponent();

	// Setup (asumed) atached input component
	void SetupInputComponent();

	// Return hit for first phyics body in reach
	FHitResult GetFirstPhyicsBodyInReach() const;

	// Returns current start of reach line
	FVector GetReachLineStart() const;

	// Returns current end of reach line
	FVector GetReachLineEnd() const;
};
