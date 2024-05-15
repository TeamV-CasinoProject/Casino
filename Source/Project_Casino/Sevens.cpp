// Fill out your copyright notice in the Description page of Project Settings.


#include "Sevens.h"
#include "Card.h"

TQueue<int32> ASevens::UnderNumQueue;
TQueue<int32> ASevens::UpNumQueue;

ASevens::ASevens()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASevens::BeginPlay()
{
	Super::BeginPlay();
	SetGame();

	CurrentPlayerNum = 0;
	Ranking = 0;
	for (int i = 0; i < PlayerNum; i++)
	{
		PlayerCards[i] = 13;
		Passes[i] = 5;
		Line[i] = 707;
		IsHasLost[i] = 0;
	}
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

	for (int i = 0; i < PlayerNum; i++)
	{		
		for (int j = i * 13; j < (i + 1) * 13; j++)
		{
			if (i % 2 == 0)
			{
				FVector SpawnLocation = FVector(i * 350 - 350, (j - (i * 13)) * 35 - 210, 350);
				SpawnCard(SpawnLocation, FRotator(0, 0, 0), FActorSpawnParameters(), Deck[j], i);
			}
			else
			{
				FVector SpawnLocation = FVector((j - (i * 13)) * 35 - 210, (i - 1) * 750 - 750, 350);
				SpawnCard(SpawnLocation, FRotator(0, 90, 0), FActorSpawnParameters(), Deck[j], i);
			}
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
}
