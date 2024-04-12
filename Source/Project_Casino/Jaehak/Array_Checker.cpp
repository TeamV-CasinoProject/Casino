// Fill out your copyright notice in the Description page of Project Settings.


#include "Array_Checker.h"

// Sets default values
AArray_Checker::AArray_Checker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AArray_Checker::BeginPlay()
{
    Super::BeginPlay();

    // �迭 ũ�� ���� (��: 3x3 �迭)
    int32 NumRows = 6;
    int32 NumCols = 6;

    // �� �ݺ�
    for (int32 i = 0; i < NumRows; ++i)
    {
        // ���ο� �� �߰�
        TArray<int32> RowArray;

        // �� �ݺ�
        for (int32 j = 0; j < NumCols; ++j)
        {
            // �� ��Ҹ� 0���� ����
            RowArray.Add(1);
        }
        // ���� ���� 2���� �迭�� �߰�
        Arr.Add(RowArray);
    }

    PrintArray();

    RotationArray(Arr, 0, 0, 2, 2);       
    
    PrintArray();

}

// Called every frame
void AArray_Checker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArray_Checker::PrintArray()
{
    for (int32 i = 0; i < Arr.Num(); ++i)
    {
        for (int32 j = 0; j < Arr[i].Num(); ++j)
        {
            UE_LOG(LogTemp, Warning, TEXT("SlotValue[%d][%d] = %d"), i, j, Arr[i][j]);
        }
    }
}

void AArray_Checker::RotationArray(TArray< TArray<int32>> Arr, int32 StartRow, int32 StartCol, int32 EndRow, int32 EndCol)
{
    int32 NumRows = EndRow - StartRow + 1;
    int32 NumCols = EndCol - StartCol + 1;

    TArray< TArray<int32>> TempArray;
    for (int32 RowIndex = 0; RowIndex < NumRows; ++RowIndex)
    {
        TArray<int32> TempRowArray;
        for (int32 ColIndex = 0; ColIndex < NumCols; ++ColIndex)
        {
            TempRowArray.Add(Arr[StartRow + RowIndex][StartCol + ColIndex]);
        }
        TempArray.Add(TempRowArray);
    }

    // �ӽ� �迭�� �ð�������� ȸ���Ͽ� ȸ���� ������ ����
    for (int32 RowIndex = 0; RowIndex < NumRows; ++RowIndex)
    {
        for (int32 ColIndex = 0; ColIndex < NumCols; ++ColIndex)
        {
            Arr[StartRow + RowIndex][StartCol + ColIndex] = TempArray[NumRows - ColIndex - 1][RowIndex];
        }
    }
}
