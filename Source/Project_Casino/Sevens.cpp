// Fill out your copyright notice in the Description page of Project Settings.


#include "Sevens.h"
#include "Card.h"
#include "UI_SevensWinResult.h"

ASevens::ASevens()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASevens::BeginPlay()
{
	Super::BeginPlay();
	SetGame();

	CurrentPlayerNum = 0;
	RankStack = 0;
	Ranking = 0;
	for (int i = 0; i < PlayerNum; i++)
	{
		PlayerCards[i] = 13;
		if(i == 0)
			Passes[i] = 5;
		else
			Passes[i] = 0;
		Line[i] = 707;
		IsHasLost[i] = 0;
	}
	endGame = false;
}

void ASevens::SetGame()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j <= 13; j++)
		{	
			Deck.Push(Card(i, j));
		}
	}

	ShuffleDeck(Deck);

	//Dumy Card for Event Dispatcher
	SpawnCard(FVector(0, 0, 0), FRotator(0, 0, 0), FActorSpawnParameters(), Card(), -1);

	float inc = 0.005f;
	for (int i = 0; i < PlayerNum; i++)
	{		
		for (int j = i * 13; j < (i + 1) * 13; j++)
		{
			if (i % 2 == 0)
			{
				FVector SpawnLocation = FVector(i * 350 - 350, (j - (i * 13)) * 35 - 210, 550 + inc);
				if(i == 0)
					SpawnCard(SpawnLocation, FRotator(0, 0, 180), FActorSpawnParameters(), Deck[j], i);
				else
					SpawnCard(SpawnLocation, FRotator(0, 0, 0), FActorSpawnParameters(), Deck[j], i);
			}
			else
			{
				FVector SpawnLocation = FVector((j - (i * 13)) * 35 - 210, (i - 1) * 650 - 650, 550 + inc);
				SpawnCard(SpawnLocation, FRotator(0, 90, 0), FActorSpawnParameters(), Deck[j], i);
			}
			inc += 0.005f;
		}
	}
}

void ASevens::ShuffleDeck(TArray<Card>& _Deck)
{
	int DeckSize = _Deck.Num();
	for (int i = 0; i < DeckSize; i++)
	{
		int RandomIdx = FMath::RandRange(0, DeckSize - 1);

		Card Tmp = _Deck[i];
		_Deck[i] = _Deck[RandomIdx];
		_Deck[RandomIdx] = Tmp;
	}
}

void ASevens::SpawnCard(FVector SpawnLocation, FRotator Rotator, FActorSpawnParameters SpawnParams, Card _Card, int Num)
{
	ACardInHands* NewCard = GetWorld()->SpawnActor<ACardInHands>(
		ACardInHands::StaticClass(), SpawnLocation, Rotator, SpawnParams);

	NewCard->SetMyself(_Card.GetSuit(), _Card.GetNum());
	NewCard->SetPlayerNum(Num);
	NewCard->SevensGameMode = this;
}
