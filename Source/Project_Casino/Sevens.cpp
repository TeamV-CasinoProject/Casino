// Fill out your copyright notice in the Description page of Project Settings.


#include "Sevens.h"

ASevens::ASevens()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASevens::BeginPlay()
{
	Super::BeginPlay();
	SetGame();
}

void ASevens::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASevens::SetGame()
{
	//Reset Card
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j <= 13; j++)
		{	
			Deck.Push(Card(i, j));
		}
	}

	//Shuffle Card
	ShuffleDeck(Deck);

	//Print Test
	for (int i = 0; i < Deck.Num(); i++)
	{
		Deck[i].PrintSuit();
	}

	//Hand Out Cards to Players
	for (int i = 0; i < PlayerNum; i++)
	{
		Players[i].SetHands(Deck, i * 13, (i + 1) * 13);
	}
}

void ASevens::SetPlayers()
{
	for (int i = 0; i < PlayerNum; i++)
	{
		Players.Push(GamePlayer(false));
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