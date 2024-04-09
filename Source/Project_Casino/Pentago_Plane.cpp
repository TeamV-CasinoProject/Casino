// Fill out your copyright notice in the Description page of Project Settings.


#include "Pentago_Plane.h"

// Sets default values for this component's properties
UPentago_Plane::UPentago_Plane()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPentago_Plane::BeginPlay()
{
	Super::BeginPlay();
	
	AActor* Owner = GetOwner();
}


// Called every frame
void UPentago_Plane::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

