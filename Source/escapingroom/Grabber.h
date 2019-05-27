// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Public/CollisionQueryParams.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPINGROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()	
private:
	UPROPERTY(EditAnywhere)
		float Reach = 100.f;
	UPhysicsHandleComponent* physics=nullptr;
	UInputComponent*input = nullptr;
	// recast and grab things in reach area
	void Grab();
	void ActionGrab();
	void Release();
	bool grabingthing;
	FVector Getplayerlocation();
	FVector GetplayerReach();
public:	
	// Sets default values for this component's properties

	UGrabber();

protected:
	// Called when the game starts
	AActor*Owner = GetOwner();
	FVector location;
	FRotator rotation;
	virtual void BeginPlay() override;

	void GetInputComponent();

	void GetPhysicsHandle();
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FHitResult ObjectInReach();
	
		
};
