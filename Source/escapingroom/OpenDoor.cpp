// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

#include "Engine/DemoNetDriver.h"

#include "GameFramework/Actor.h"
#include "Engine/World.h"
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	 player=GetWorld()->GetFirstPlayerController()->GetPawn();
	 if (PressurePlat == nullptr) {
		 UE_LOG(LogTemp, Error, TEXT("we are missig pressure plate"))
	 
	 }
	
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//askes every frame if the player is on the pressure plate
	if (GetTotalMassOnPlate()>threshold) {

		FOnOpenRequest.Broadcast();		

	}
	else {
		FOnCloseRequest.Broadcast();
	}
	
}
float UOpenDoor::GetTotalMassOnPlate() {
	float TotalMass = 0;
	TArray<AActor*> OverlappingObjects;
	if (PressurePlat) {
		PressurePlat->GetOverlappingActors(OUT OverlappingObjects);
		for (auto&actor : OverlappingObjects) {
			TotalMass = actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}
	
	return TotalMass;
}