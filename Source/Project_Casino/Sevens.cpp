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
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j <= 13; j++)
		{	
			Deck.Push(Card(i, j));
		}
	}

	ShuffleDeck(Deck);

	//print test
	for (int i = 0; i < Deck.Num(); i++)
	{
		Deck[i].PrintSuit();
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