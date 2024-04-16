// Fill out your copyright notice in the Description page of Project Settings.


#include "WinChecker.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AWinChecker::AWinChecker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWinChecker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWinChecker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


TArray<AActor*> AWinChecker::Sorting(TArray<AActor*> arr)
{
	arr.Sort();

	for (int32 Index = 0; Index < arr.Num(); ++Index)
	{

		AActor* Actor = arr[Index];
		FString ActorName = Actor->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"), *(arr[Index]->GetName()));
	}

	TArray<AActor*> Subarr;
	Subarr.Init(nullptr, arr.Num());

	for (int i = 0; i < arr.Num(); i++)
	{
		// 1 ~ 3 & 19 ~ 21
		// 16 ~ 18 & 34 ~36
		Subarr[i] = arr[i];
		// 4 ~ 6 & 22 ~ 24
		if ((i >= 3 && i <= 5) || (i >= 21 && i <= 23))
			Subarr[i] = arr[i + 6];
		// 7 ~ 9 & 25 ~ 27
		if ((i >= 6 && i <= 8) || (i >= 24 && i <= 26))
			Subarr[i] = arr[i + 3];
		// 10 ~ 12 & 28 ~ 30
		if ((i >= 9 && i <= 11) || (i >= 27 && i <= 29))
			Subarr[i] = arr[i - 3];
		// 13 ~ 15 & 31 ~ 33
		if ((i >= 12 && i <= 14) || (i >= 30 && i <= 32))
			Subarr[i] = arr[i - 6];
	}

	for (int i = 0; i < arr.Num(); i++)
	{
		arr[i] = Subarr[i];

		AActor* CurrentActor = arr[i];
		FString ActorName = CurrentActor->GetName();
		UE_LOG(LogTemp, Warning, TEXT("액터 이름: %s, 배열 순서: %d"), *ActorName, i);
	}


	return arr;
}

void AWinChecker::SortingAnd2D(TArray<float> arr)
{
	// 입력 배열의 요소 개수가 충분한지 확인합니다.
	if (arr.Num() < 36)
	{
		UE_LOG(LogTemp, Error, TEXT("Input array should have at least 36 elements"));
		return;
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			NewArr[i][j] = arr[(6 * i) + j];
		}
	}
}
float AWinChecker::WinCheck()
{

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			// 가로
			if (NewArr[i][j] == white && NewArr[i][j + 1] == white && NewArr[i][j + 2] == white && NewArr[i][j + 3] == white && NewArr[i][j + 4] == white)
			{
				return white;
			}
			else if (NewArr[i][j] == black && NewArr[i][j + 1] == black && NewArr[i][j + 2] == black && NewArr[i][j + 3] == black && NewArr[i][j + 4] == black)
			{
				return black;
			}

			// 세로
			if (NewArr[i][j] == white && NewArr[i + 1][j] == white && NewArr[i + 2][j] == white && NewArr[i + 3][j] == white && NewArr[i + 4][j] == white)
			{
				return white;
			}
			else if (NewArr[i][j] == black && NewArr[i + 1][j] == black && NewArr[i + 2][j] == black && NewArr[i + 3][j] == black && NewArr[i + 4][j] == black)
			{
				return black;
			}
		}
	}

	// 대각선 
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			// 대각선 1
			if (NewArr[i][j] == white && NewArr[i + 1][j + 1] == white && NewArr[i + 2][j + 2] == white && NewArr[i + 3][j + 3] == white && NewArr[i + 4][j + 4] == white)
			{
				return white;
			}
			else if (NewArr[i][j] == black && NewArr[i + 1][j + 1] == black && NewArr[i + 2][j + 2] == black && NewArr[i + 3][j + 3] == black && NewArr[i + 4][j + 4] == black)
			{
				return black;
			}

			// 대각선 2
			if (NewArr[i][j] == white && NewArr[i + 1][j - 1] == white && NewArr[i + 2][j - 2] == white && NewArr[i + 3][j - 3] == white && NewArr[i + 4][j - 4] == white)
			{
				return white;
			}
			else if (NewArr[i][j] == black && NewArr[i + 1][j - 1] == black && NewArr[i + 2][j - 2] == black && NewArr[i + 3][j - 3] == black && NewArr[i + 4][j - 4] == black)
			{
				return black;
			}
		}
	}

	return 0.0f;
}

