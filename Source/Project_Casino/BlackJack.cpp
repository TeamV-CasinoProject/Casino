// Fill out your copyright notice in the Description page of Project Settings.

#include <iostream>
#include <vector>
#include <algorithm>
#include "TimerManager.h"
#include "BlackJack.h"
#include"TestCard.h"

void ABlackJack::InitGame()
{
	PlayerCount = 3;

	for (int i = 0; i < PlayerCount + 1; i++)
	{
		PlayerList.Push(PlayerInfo());
	}
	SetDeck();
}

void ABlackJack::SetDeck()
{
	for (int i = 0; i < 4; i++)
		for (int k = 1; k < 14; k++)
			for (int j = 0; j < 4; j++)
			{
				Card c(i, k);
				Deck.Push(Card(i, k));
			}
	
	for (int i = 0; i < 52*4 - 1; i++)
	{
		int j = i + rand() % (52*4 - i);
		std::swap(Deck[i], Deck[j]);
	}
}

void ABlackJack::Bet()
{
	for (PlayerPoint = 0; PlayerPoint < PlayerCount + 1; PlayerPoint++)
		PlayerList[PlayerPoint].Init();
	PlayerPoint = 0;
	IsDealerTurn = false;

	InitRound();
}

void ABlackJack::Double()
{
}

void ABlackJack::InitRound()
{
	for (PlayerPoint = 0; PlayerPoint < PlayerCount; PlayerPoint++)
		Hit();
	Hit();

	for (PlayerPoint = 0; PlayerPoint < PlayerCount; PlayerPoint++)
		Hit();

	for (PlayerPoint = 0; PlayerPoint < PlayerCount; PlayerPoint++)
	{
		if(PlayerList[PlayerPoint].Hand[0].GetNum() == PlayerList[PlayerPoint].Hand[1].GetNum())
			UE_LOG(LogTemp, Warning, TEXT("%d Player  Double"), PlayerPoint);
	}
	PlayerPoint = 0;
}

void ABlackJack::DoubleDown()
{
	Hit();
	Stay();
}

void ABlackJack::Calc()
{
	int sum = PlayerList[PlayerPoint].CalcSum();

	if (!IsDealerTurn)
	{
		if (sum > 21)
		{
			UE_LOG(LogTemp, Warning, TEXT("%d Player Burst"), PlayerPoint);
			PlayerList[PlayerPoint].Sum = -1;
			Stay();
		}
	}
	else
		if (sum < 16)
		{
			Hit();
		}
		else if (sum > 21)
		{
			p4 = "-1";
			PlayerList[PlayerCount].Sum = 0;
			RoundEnd();
		}
		else
			RoundEnd();
	p1 = FString::Printf(TEXT("%d"), PlayerList[0].Sum);
	p2 = FString::Printf(TEXT("%d"), PlayerList[1].Sum);
	p3 = FString::Printf(TEXT("%d"), PlayerList[2].Sum);
	p4 = FString::Printf(TEXT("%d"), PlayerList[3].Sum);
}

void ABlackJack::AddCard(AActor* c)
{
	PlayerList[PlayerCount].CardActor.Push(c);
}

void ABlackJack::SpawnCard()
{
		UObject* cls = StaticLoadObject(UObject::StaticClass(), nullptr, TEXT("/Script/Engine.Blueprint'/Game/Siruduk/BP/BP_TestCard.BP_TestCard'"));
		UBlueprint* bp = Cast<UBlueprint>(cls);
		TSubclassOf<class UObject> blockBP = (UClass*)bp->GeneratedClass;
		FVector v = CardPos[PlayerPoint] + FVector(-5,-5, 0) * PlayerList[PlayerPoint].Hand.Num();
		UObject* c = GetWorld()->SpawnActor<UObject>(blockBP, v, FRotator(0, -90, 0));
		ATestCard* tc = Cast<ATestCard>(c);
		if (tc)
			tc->Set(Deck[DeckPoint].GetNum());
		PlayerList[PlayerPoint].CardActor.Push(c);
}

int ABlackJack::Getnum()
{
	return PlayerList[PlayerPoint].Hand.Top().GetNum();
}

void ABlackJack::RoundEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("RoundEnd"));	
	EndRoundEvent.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Dealer %d"), PlayerList[PlayerCount].Sum);
	int Dealer = PlayerList[PlayerCount].Sum;
	for (int i = 0; i < PlayerCount; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d Player Sum : %d"), i,PlayerList[i].Sum);
		if (PlayerList[i].Sum > Dealer)
		{
			if (PlayerList[i].Sum == 21)
			{
				UE_LOG(LogTemp, Warning, TEXT("%d Player win BlackJack * 2.5"), i);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("%d Player win * 2"), i);

		}
		else if (PlayerList[i].Sum == Dealer)
		{
			UE_LOG(LogTemp, Warning, TEXT("%d Player Draw"), i);
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("%d Player Loser"), i);
		if (Dealer == 21)
			return;
	}
}

void ABlackJack::Stay()
{
	UE_LOG(LogTemp, Warning, TEXT("%d Player End"), PlayerPoint);
	PlayerPoint++;
	if (PlayerCount == PlayerPoint)
	{
		IsDealerTurn = true;
		Calc();
	}
	else if (PlayerCount > PlayerPoint)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d Player Turn	  Sum : %d"), PlayerPoint,PlayerList[PlayerPoint].Sum);
	}
	ChangePlayerEvent.Broadcast();
}

void ABlackJack::Insurance()
{

}

void ABlackJack::Hit()
{
	UE_LOG(LogTemp, Warning, TEXT("%d Player  %d"), PlayerPoint, Deck[DeckPoint].GetNum());
	SpawnCard();
	PlayerList[PlayerPoint].Hand.Push(Deck[DeckPoint++]);
	Calc();

}

/*

*/

void PlayerInfo::Init()
{
	Hand.Empty();
	Coin = 0;
	InsuranceCoin = 0;
	for (auto It = CardActor.begin(); It != CardActor.end(); ++It)
	{
		UObject* c = *It;
		c->ConditionalBeginDestroy();
	}
	CardActor.Empty();
}

int PlayerInfo::CalcSum() {
	 int AceCount = 0;
	 Sum = 0;
	for (auto It = Hand.begin(); It != Hand.end(); ++It)
	{
		Card Element = *It;
		if (Element.GetNum() > 9)
			Sum += 10;
		else
			Sum += Element.GetNum();
		if (Element.GetNum() == 1)
		{
			AceCount++;
			Sum += 10;
		}
		if (Sum > 21 && AceCount > 0)
		{
			AceCount--;
			Sum -= 10;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Player sum %d"),Sum);

	return Sum;
}


