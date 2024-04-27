// Fill out your copyright notice in the Description page of Project Settings.


#include "Sevens.h"
#include "Card.h"

ASevens::ASevens()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = APlayerPawn::StaticClass();
}

void ASevens::BeginPlay()
{
	Super::BeginPlay();
	SetPlayers();
	SetGame();

	CurrentPlayerNum = 0;
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

	//패에 있는 카드를 화면에 나열하는 코드
	for (int i = 0; i < PlayerNum; i++)
	{
		TArray<Card> Hands = *(Players[i].GetHands());
		for (int j = 0; j < Hands.Num(); j++)
		{
			if (i % 2 == 0)
			{
				FVector SpawnLocation = FVector(i * 600 - 600, j * 100 - 600, 400);
				SpawnCard(SpawnLocation, FRotator(0, 0, 0), FActorSpawnParameters(), Hands[i]);
			}
			else
			{
				FVector SpawnLocation = FVector(j * 100 - 600, i * 1400 - 2800, 400);
				SpawnCard(SpawnLocation, FRotator(0, 90, 0), FActorSpawnParameters(), Hands[i]);
			}
			
		}
	}
}

void ASevens::SetPlayers()
{
	for (int i = 0; i < PlayerNum; i++)
	{
		Players.Push(GamePlayer());
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

void ASevens::TakeATurn(Card Selected)
{
	Players[CurrentPlayerNum].RemoveCardToHands(Selected);

	//PlayCard();
	MoveToNextTurn();
}

void ASevens::SpawnCard(FVector SpawnLocation, FRotator Rotator, FActorSpawnParameters SpawnParams, Card _Card)
{
	ACardInHands* NewCard = GetWorld()->SpawnActor<ACardInHands>(
		ACardInHands::StaticClass(), SpawnLocation, Rotator, SpawnParams);

	NewCard->SetMyself(_Card.GetSuit(), _Card.GetNum());
}

void ASevens::MoveToNextTurn()
{
	CurrentPlayerNum++;
	if (CurrentPlayerNum == 4) CurrentPlayerNum = 0;
}

void ASevens::PlayCard()
{
	//카드를 내는 작업 - 실제 카드 인스턴스를 생성하고 화면의 적절한 위치로 이동
}
