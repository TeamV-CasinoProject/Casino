#include "OthelloSlot.h"

AOthelloSlot::AOthelloSlot()
{
    PrimaryActorTick.bCanEverTick = false;
    SlotState = ESlotState::Empty;
}

void AOthelloSlot::BeginPlay()
{
    Super::BeginPlay();
}

void AOthelloSlot::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AOthelloSlot::UpdatePieceVisual()
{
    if (SlotState == ESlotState::Empty)
    {
        DestroyPiece();
    }
    else
    {
        if (!CurrentPiece)
        {
            SpawnPiece();
        }

        if (CurrentPiece)
        {
            // 피스 회전 (흰색 상태의 경우)
            if (SlotState == ESlotState::White)
            {
                CurrentPiece->SetActorRotation(FRotator(0, 180.0f, 0));
            }
            else // Black 상태
            {
                CurrentPiece->SetActorRotation(FRotator::ZeroRotator);
            }
        }
    }
}

void AOthelloSlot::SpawnPiece()
{
    if (PieceClass && !CurrentPiece)
    {
        FVector Location = GetActorLocation();
        Location.Z += 70.0f; // Adjust this value as needed
        FRotator Rotation = GetActorRotation();

        CurrentPiece = GetWorld()->SpawnActor<AOthelloPiece>(PieceClass, Location, Rotation);
        if (CurrentPiece)
        {
            CurrentPiece->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
        }
    }
}

void AOthelloSlot::SetState(ESlotState NewState)
{
    if (SlotState != NewState)
    {
        SlotState = NewState;
        UpdatePieceVisual();
    }
}

void AOthelloSlot::DestroyPiece()
{
    if (CurrentPiece)
    {
        CurrentPiece->Destroy();
        CurrentPiece = nullptr;
    }
}