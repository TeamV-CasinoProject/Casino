// Fill out your copyright notice in the Description page of Project Settings.


#include "OthelloBoard.h"
#include "Engine/World.h"

// Sets default values
AOthelloBoard::AOthelloBoard()
{
    PrimaryActorTick.bCanEverTick = true;

    // Initialize the GridSlots array with nullptr
    for (int32 i = 0; i < MAX_BOARD_SIZE; i++)
    {
        for (int32 j = 0; j < MAX_BOARD_SIZE; j++)
        {
            GridSlots[i][j] = nullptr;
        }
    }
}

// Called when the game starts or when spawned
void AOthelloBoard::BeginPlay()
{
	Super::BeginPlay();
    CreateGrid();
    PlaceInitialPieces();
	
}

// Called every frame
void AOthelloBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOthelloBoard::CreateGrid()
{
    if (SlotClass && BoardSize <= MAX_BOARD_SIZE)
    {
        FVector BoardCenter = GetActorLocation();
        FRotator BoardRotation = GetActorRotation();
        FVector StartPosition = BoardCenter + BoardRotation.RotateVector(FVector(350, -350, 0));

        for (int32 Col = 0; Col < BoardSize; Col++)
        {
            for (int32 Row = 0; Row < BoardSize; Row++)
            {
                FVector SlotLocation = StartPosition + BoardRotation.RotateVector(FVector(-Col * SlotSpacing, Row * SlotSpacing, 0));
                AOthelloSlot* NewSlot = GetWorld()->SpawnActor<AOthelloSlot>(SlotClass, SlotLocation, BoardRotation);
                if (NewSlot)
                {
                    NewSlot->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
                    int32 SlotIndex = Col * BoardSize + Row;
                    NewSlot->SetActorLabel(FString::Printf(TEXT("Slot_%d"), SlotIndex));

                    // Store the slot in the 2D array
                    GridSlots[Col][Row] = NewSlot;
                }
            }
        }
    }
}

AOthelloSlot* AOthelloBoard::GetSlotAt(int32 Col, int32 Row)
{
    if (Col >= 0 && Col < BoardSize && Row >= 0 && Row < BoardSize)
    {
        return GridSlots[Col][Row];
    }
    return nullptr;
}


void AOthelloBoard::PlaceInitialPieces()
{
    if (BoardSize < 4 || !PieceClass)
    {
        return;
    }

    int32 Center = BoardSize / 2 - 1;

    // Place white pieces
    PlacePieceAt(Center, Center, false);
    PlacePieceAt(Center + 1, Center + 1, false);

    // Place black pieces
    PlacePieceAt(Center, Center + 1, true);
    PlacePieceAt(Center + 1, Center, true);
}

void AOthelloBoard::PlacePieceAt(int32 Col, int32 Row, bool IsBlack)
{
    AOthelloSlot* Slot = GetSlotAt(Col, Row);
    if (Slot)
    {
        ESlotState NewState = IsBlack ? ESlotState::Black : ESlotState::White;
        Slot->SetState(NewState);
    }
}