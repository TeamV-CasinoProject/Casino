// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Math/UnrealMathUtility.h"
#include "GamePlayer.h"
#include "CardInHands.h"
#include "Engine/World.h"
#include "Sevens.generated.h"

class Card;

static const int PlayerNum = 4;
static const int SuitNum = 4;

UCLASS()
class PROJECT_CASINO_API ASevens : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASevens();

protected:
	virtual void BeginPlay() override;

public:
	void SetGame();
	void SetPlayers();
	void ShuffleDeck(TArray<Card>&);
	void SpawnCard(FVector, FRotator, FActorSpawnParameters, Card, int);

	static int CurrentPlayerNum;
	static int PlayerCards[PlayerNum];
	static int Passes[PlayerNum];
	static int Line[SuitNum];
	
private:
	TArray<Card> Deck;
	TArray<GamePlayer> Players;
};

int ASevens::CurrentPlayerNum = 0;
int ASevens::PlayerCards[PlayerNum]{ 0, 0, 0, 0 };
int ASevens::Passes[PlayerNum]{ 0, 0, 0, 0 };
int ASevens::Line[SuitNum]{ 0, 0, 0, 0 };