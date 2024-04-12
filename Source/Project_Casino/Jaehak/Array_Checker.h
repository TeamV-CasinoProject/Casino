// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Array_Checker.generated.h"

//typedef TArray < TArray<int32>> TwoDimArr;

UCLASS()
class PROJECT_CASINO_API AArray_Checker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArray_Checker();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//TwoDimArr Arr;

	TArray< TArray<int32>> Arr;

	void PrintArray();

	void RotationArray(TArray< TArray<int32>> Arr, int32 StartRow, int32 StartCol, int32 EndRow, int32 EndCol);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
