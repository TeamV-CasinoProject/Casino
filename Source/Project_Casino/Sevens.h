// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Math/UnrealMathUtility.h"
#include "Card.h"
#include "GamePlayer.h"
#include "Sevens.generated.h"

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

	void PlayCard();

private:
	TArray<Card> Deck;
	TArray<GamePlayer> Players;

	int CurrentPlayerNum;
};
