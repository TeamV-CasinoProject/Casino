// Fill out your copyright notice in the Description page of Project Settings.


#include "Check_Slot.h"

// Sets default values for this component's properties
UCheck_Slot::UCheck_Slot()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCheck_Slot::SettingSlots()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			slots[i][j] = 0;
		}
	}
}


// Called when the game starts
void UCheck_Slot::BeginPlay()
{
	Super::BeginPlay();
	SettingSlots();

	UE_LOG(LogTemp, Display, TEXT("%d"),slots[0][0]);

	// ...
	
}


// Called every frame
void UCheck_Slot::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

