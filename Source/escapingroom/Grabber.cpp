// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/DemoNetDriver.h"

#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber report for reporting duty!"));
	// ...
	/// lock for attached physcis handle by going ot owner then get the phycishandle component
	GetPhysicsHandle();
	GetInputComponent();
	grabingthing = false;
}

void UGrabber::GetInputComponent()
{
	input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (input) {
		input->BindAction("Grab", IE_Pressed, this, &UGrabber::ActionGrab);
		
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("error %s attached input handler not found"), *GetOwner()->GetName())
	}
}

void UGrabber::GetPhysicsHandle()
{
	physics = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physics==nullptr) {
		UE_LOG(LogTemp, Error, TEXT("error %s attached physics handler not found"), *GetOwner()->GetName())
	}
	
}

void UGrabber::ActionGrab() {
	
	if (!grabingthing)
	{///get object in reach
		Grab();
		
	}
	else Release();
	grabingthing = !grabingthing;
}
void UGrabber::Grab()
{
	auto HitResult = ObjectInReach(); auto component = HitResult.GetComponent();
	auto actor = HitResult.GetActor();
	///attach it ot pyhiscs handle or in a simple way to grab it
	if (actor)
	{		if (HitResult.GetActor())
			physics->GrabComponent(
				component,
				NAME_None,
				component->GetOwner()->GetActorLocation(),
				true //allowrotation
			);
	}
}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	/// get player view point
	location = Owner->GetActorLocation();
	rotation = Owner->GetActorRotation();
	///move object grabbed with the player
	if (physics->GrabbedComponent)
		physics->SetTargetLocation(GetplayerReach());
}

FHitResult UGrabber::ObjectInReach()
{	
	///get player location and reach
	FVector PointOfViewLocation=Getplayerlocation();
	FVector LineTraceEndPoint = GetplayerReach();
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	///line-trace to see what is in the player reach
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PointOfViewLocation,
		LineTraceEndPoint,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	return Hit;
}

void UGrabber::Release() {
	physics->ReleaseComponent();
}
FVector UGrabber::Getplayerlocation() {
	FVector PointOfViewLocation;
	FRotator PointOfViewRotation;
	///get player point of view
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PointOfViewLocation, PointOfViewRotation);
	FVector unitvectortoplayer = PointOfViewRotation.Vector();
	return PointOfViewLocation;

}
FVector UGrabber::GetplayerReach() {
	FVector PointOfViewLocation;
	FRotator PointOfViewRotation;
	///get player point of view
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PointOfViewLocation, PointOfViewRotation);
	FVector unitvectortoplayer = PointOfViewRotation.Vector();
	FVector LineTraceEndPoint = unitvectortoplayer * Reach + PointOfViewLocation;
	return LineTraceEndPoint;
}