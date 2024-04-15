// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrayChecker.h"

// Sets default values for this component's properties
UArrayChecker::UArrayChecker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UArrayChecker::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UArrayChecker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UArrayChecker::Check(TArray<float> arr)
{
	float NewArr[6][6] = {};

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			NewArr[i][j] = arr[(6 * i) + (j + 1)];

		}
	}


}