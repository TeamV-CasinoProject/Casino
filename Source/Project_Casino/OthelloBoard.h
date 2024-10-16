#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OthelloSlot.h"
#include "OthelloPiece.h"
#include "OthelloBoard.generated.h"

UCLASS()
class PROJECT_CASINO_API AOthelloBoard : public AActor
{
    GENERATED_BODY()

public:
    AOthelloBoard();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Othello")
    int32 BoardSize = 8;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Othello")
    TSubclassOf<AOthelloSlot> SlotClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Othello")
    TSubclassOf<AOthelloPiece> PieceClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Othello")
    float SlotSpacing = 100.0f;

    UFUNCTION(BlueprintCallable, Category = "Othello")
    AOthelloSlot* GetSlotAt(int32 Col, int32 Row);

    void PlacePieceAt(int32 Col, int32 Row, bool IsBlack);

private:
    void CreateGrid();
    void PlaceInitialPieces();

    static const int32 MAX_BOARD_SIZE = 8;
    AOthelloSlot* GridSlots[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
};