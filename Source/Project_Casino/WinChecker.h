// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WinChecker.generated.h"


class ABP_Pentago_Checker;
UCLASS()
class PROJECT_CASINO_API AWinChecker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWinChecker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "ArrCheck")
	TArray < AActor*> Sorting(TArray<AActor*> arr);

	UFUNCTION(BlueprintCallable, Category = "ArrCheck")
	void SortingAnd2D(TArray<float> arr);

	UFUNCTION(BlueprintCallable, Category = "ArrCheck")
	float WinCheck();


	int32 CheckPatterns(int32 Value);

private:

	float NewArr[6][6];
	float white;
	float black ;

	//float testA(float NewArr[6][6]);
	//UFUNCTION(BlueprintCallable, Category = "ArrCheck")
	//void testB();
};
