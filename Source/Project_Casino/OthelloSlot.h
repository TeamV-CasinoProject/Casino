#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OthelloPiece.h"
#include "OthelloSlot.generated.h"

UENUM(BlueprintType)
enum class ESlotState : uint8
{
    Empty,
    White,
    Black
};

UCLASS()
class PROJECT_CASINO_API AOthelloSlot : public AActor
{
    GENERATED_BODY()

public:
    AOthelloSlot();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Othello")
    ESlotState SlotState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Othello")
    TSubclassOf<AOthelloPiece> PieceClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Othello")
    AOthelloPiece* CurrentPiece;

    UFUNCTION(BlueprintCallable, Category = "Othello")
    void SetState(ESlotState NewState);

    UFUNCTION(BlueprintCallable, Category = "Othello")
    void UpdatePieceVisual();

private:
    void SpawnPiece();
    void DestroyPiece();
};