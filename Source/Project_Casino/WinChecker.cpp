// Fill out your copyright notice in the Description page of Project Settings.


#include "WinChecker.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AWinChecker::AWinChecker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			NewArr[i][j] = 0.0f;
		}
	}

	white = 1.0f;
	black = 2.0f;
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
			Subarr[i] = arr[i - 3];
		// 10 ~ 12 & 28 ~ 30
		if ((i >= 9 && i <= 11) || (i >= 27 && i <= 29))
			Subarr[i] = arr[i + 3];
		// 13 ~ 15 & 31 ~ 33
		if ((i >= 12 && i <= 14) || (i >= 30 && i <= 32))
			Subarr[i] = arr[i - 6];
	}

	for (int i = 0; i < arr.Num(); i++)
	{
		arr[i] = Subarr[i];
	}

	return arr;
}


void AWinChecker::SortingAnd2D(TArray<float> arr)
{
	if (arr.Num() < 36)
	{
		UE_LOG(LogTemp, Error, TEXT("under 36"));
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
    int32 Result = CheckPatterns(white);
    if (Result != 0)
        return Result;

    Result = CheckPatterns(black);
    if (Result != 0)
        return Result;

    return 0.0f;
}

int32 AWinChecker::CheckPatterns(int32 Value)
{
    // 가로 및 세로 검사
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            // 가로
            if (j + 4 < 6 && NewArr[i][j] == Value && NewArr[i][j + 1] == Value && 
                NewArr[i][j + 2] == Value && NewArr[i][j + 3] == Value && NewArr[i][j + 4] == Value)
            {
                if (j + 5 < 6 && NewArr[i][j + 5] == Value)
                    return 0;
                return Value;
            }

            // 세로
            if (i + 4 < 6 && NewArr[i][j] == Value && NewArr[i + 1][j] == Value && 
                NewArr[i + 2][j] == Value && NewArr[i + 3][j] == Value && NewArr[i + 4][j] == Value)
            {
                if (i + 5 < 6 && NewArr[i + 5][j] == Value)
                    return 0;
                return Value;
            }
        }
    }

    // 대각선 검사
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            // 대각선 1
            if (i + 4 < 6 && j + 4 < 6 && NewArr[i][j] == Value && NewArr[i + 1][j + 1] == Value && 
                NewArr[i + 2][j + 2] == Value && NewArr[i + 3][j + 3] == Value && NewArr[i + 4][j + 4] == Value)
            {
                if (i + 5 < 6 && j + 5 < 6 && NewArr[i + 5][j + 5] == Value)
                    return 0;
                return Value;
            }

            // 대각선 2
            if (i + 4 < 6 && j - 4 >= 0 && NewArr[i][j] == Value && NewArr[i + 1][j - 1] == Value && 
                NewArr[i + 2][j - 2] == Value && NewArr[i + 3][j - 3] == Value && NewArr[i + 4][j - 4] == Value)
            {
                if (i + 5 < 6 && j - 5 >= 0 && NewArr[i + 5][j - 5] == Value)
                    return 0;
                return Value;
            }
        }
    }

    return 0;
}