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
	
}

void UOpenDoor::opendoorfunc()
{
	//creat an Actor pointer to point to the door
	AActor*Owner = GetOwner();
	// frotator to make fquat
	FRotator Open = FRotator(0, -90, 0);
	//is used in function Addactorlocalrotation
	FQuat OuatOpen = FQuat(Open);
	//rotate the door
	Owner->AddActorLocalRotation(OuatOpen, false, 0, ETeleportType::None);
}

void UOpenDoor::closedoor()
{
	//creat an Actor pointer to point to the door
	AActor*Owner = GetOwner();
	// frotator to make fquat
	FRotator close = FRotator(0, 90, 0);
	//is used in function Addactorlocalrotation
	FQuat Ouatclose = FQuat(close);
	//rotate the door
	Owner->AddActorLocalRotation(Ouatclose, false, 0, ETeleportType::None);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//askes every frame if the player is on the pressure plate
	if (PressurePlat&&PressurePlat->IsOverlappingActor( player)&&!isopen) {

		opendoorfunc();
		isopen = true;

	}

	

}

