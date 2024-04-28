// Fill out your copyright notice in the Description page of Project Settings.


#include "Sevens.h"
#include "Card.h"

ASevens::ASevens()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASevens::BeginPlay()
{
	Super::BeginPlay();
	SetPlayers();
	SetGame();

	CurrentPlayerNum = 0;
	for (int i = 0; i < PlayerNum; i++)
	{
		PlayerCards[i] = 13;
		Passes[i] = 5;
		Line[i] = 707;
	}
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

	//Hand Out Cards to Players
	for (int i = 0; i < PlayerNum; i++)
	{
		Players[i].SetHands(Deck, i * 13, (i + 1) * 13);
	}

	//패에 있는 카드를 화면에 나열하는 코드
	for (int i = 0; i < PlayerNum; i++)
	{
		TArray<Card> Hands = *(Players[i].GetHands());
		for (int j = 0; j < Hands.Num(); j++)
		{
			if (i % 2 == 0)
			{
				FVector SpawnLocation = FVector(i * 350 - 350, j * 35 - 210, 350);
				SpawnCard(SpawnLocation, FRotator(0, 0, 0), FActorSpawnParameters(), Hands[j], i);
			}
			else
			{
				FVector SpawnLocation = FVector(j * 35 - 210, (i - 1) * 750 - 750, 350);
				SpawnCard(SpawnLocation, FRotator(0, 90, 0), FActorSpawnParameters(), Hands[j], i);
			}
			
		}
	}
}

void ASevens::SetPlayers()
{
	for (int i = 0; i < PlayerNum; i++)
	{
		GamePlayer New = GamePlayer();
		Players.Add(New);
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
}
