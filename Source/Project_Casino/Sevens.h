// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Math/UnrealMathUtility.h"
#include "GamePlayer.h"
#include "CardInHands.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Engine/StaticMesh.h"
#include "Sevens.generated.h"

class Card;

static const int PlayerNum = 4;

UCLASS()
class PROJECT_CASINO_API ASevens : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASevens();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	void SetGame();
	void SetPlayers();
	void ShuffleDeck(TArray<Card>&);
	void TakeATurn(Card);
	void SpawnCard(FVector, FRotator, FActorSpawnParameters, Card);
	void MoveToNextTurn();
	void PlayCard();

private:
	TArray<Card> Deck;
	TArray<GamePlayer> Players;

	int CurrentPlayerNum;

	float TmpTime;
	int TurnProcess;
};
