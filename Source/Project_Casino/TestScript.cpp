// Fill out your copyright notice in the Description page of Project Settings.


#include "TestScript.h"

// Sets default values for this component's properties
UTestScript::UTestScript()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

FVector UTestScript::CreateLocation(float X, float Y, float Z)
{
	return FVector(X, Y, Z);
}


// Called when the game starts
void UTestScript::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTestScript::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
