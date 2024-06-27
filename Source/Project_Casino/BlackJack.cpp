
// Fill out your copyright notice in the Description page of Project Settings.

#include <iostream>
#include <vector>
#include <algorithm>
#include "TimerManager.h"
#include "BlackJack.h"
#include"TestCard.h"

void ABlackJack::InitGame()
{
	PlayerCount = 1;

	for (int i = 0; i < PlayerCount + 1; i++)
	{
		PlayerList.Push(PlayerInfo());
	}
	SetDeck();
	pscore.Push("");
	pscore.Push("");
	pscore.Push("");
	pscore.Push("");
	pend.Push("");
	pend.Push("");
	pend.Push("");
	pend.Push("");

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
	{
		PlayerList[PlayerPoint].Init();
		pscore[PlayerPoint] = "";
	}
	PlayerPoint = 0;
	IsDealerTurn = false;
	UpdateUi();
	InitRound();
}

void ABlackJack::Double()
{
}

void ABlackJack::InitRound()
{
	if (DeckPoint < 150)
		InitGame();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
		&ABlackJack::DelayHit, 1, false);

	//for (PlayerPoint = 0; PlayerPoint < PlayerCount; PlayerPoint++)
	//{
	//	if(PlayerList[PlayerPoint].Hand[0].GetNum() == PlayerList[PlayerPoint].Hand[1].GetNum())
	//		UE_LOG(LogTemp, Warning, TEXT("%d Player  Double"), PlayerPoint);
	//}
}

void ABlackJack::DoubleDown()
{
	Hit();
	Stay();
}

void ABlackJack::Calc()
{
	int sum = PlayerList[PlayerPoint].CalcSum();

	pscore[PlayerPoint] = FString::Printf(TEXT("%d"), PlayerList[PlayerPoint].Sum);
	if (!IsDealerTurn)
	{
		if (sum > 21)
		{
			UE_LOG(LogTemp, Warning, TEXT("%d Player Burst"), PlayerPoint);
			PlayerList[PlayerPoint].Sum = -1;
			pscore[PlayerPoint] = "Burst";

			Stay();
		}
	}
	else
		if (sum < 16)
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
				&ABlackJack::Hit, 1, false);
		}
		else if (sum > 21)
		{
			PlayerList[PlayerCount].Sum = 0;
			RoundEnd();
		}
		else
			RoundEnd();
	UpdateUi();

}

void ABlackJack::AddCard(AActor* c)
{
	PlayerList[PlayerCount].CardActor.Push(c);
}

void ABlackJack::SpawnCard(FRotator Rotator, FActorSpawnParameters SpawnParams, Card _Card)
{
	FVector SpawnLocation = CardPos[PlayerPoint] + FVector(-5, -5, 0.01) * PlayerList[PlayerPoint].Hand.Num();
	ATestCard* NewCard = GetWorld()->SpawnActor<ATestCard>(
		ATestCard::StaticClass(), SpawnLocation, FRotator(180.0f, 90.0f, 0.0f), SpawnParams);

	NewCard->Set(_Card.GetNum(), _Card.GetSuit());
	PlayerList[PlayerPoint].CardActor.Push(NewCard);
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
				pscore[i] = "win BlackJack * 2.5";
			}
			else
			{
				pscore[i] = "win * 2";
			}

		}
		else if (PlayerList[i].Sum == Dealer)
		{
			pscore[i] = "Draw";
		}
		else
			pscore[i] = "Lose";
		if (Dealer == 21)
		{
			pscore[i] = "Lose";
			return;
		}
		UpdateUi();
	}
}

void ABlackJack::Stay()
{
	UE_LOG(LogTemp, Warning, TEXT("%d Player End"), PlayerPoint);
	pend[PlayerPoint] = "End";
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
	UpdateUi();
	ChangePlayerEvent.Broadcast();
}

void ABlackJack::Insurance()
{

}

void ABlackJack::Hit()
{
	UE_LOG(LogTemp, Warning, TEXT("%d Player  %d"), PlayerPoint, Deck[DeckPoint].GetNum());
		SpawnCard(FRotator(0, 0, 90), FActorSpawnParameters(), Deck[DeckPoint]);
		PlayerList[PlayerPoint].Hand.Push(Deck[DeckPoint++]);
		Calc();
}

/*

*/

void ABlackJack::UpdateUi()
{
	p1 = pscore[0];
	p2 = pscore[1];
	p3 = pscore[2];
	p4 = pscore[3];
	e1 = pend[0];
	e2 = pend[1];
	e3= pend[2];

}

void ABlackJack::DelayHit()
{
	UE_LOG(LogTemp, Warning, TEXT("%d Player  %d"), PlayerPoint, Deck[DeckPoint].GetNum());
	SpawnCard(FRotator(0, 0, 90), FActorSpawnParameters(), Deck[DeckPoint]);
	PlayerList[PlayerPoint].Hand.Push(Deck[DeckPoint++]);
	Calc();
	PlayerPoint++;
	UpdateUi();
	if (PlayerPoint > PlayerCount)
		PlayerPoint = 0;

	if (count < (PlayerCount + 1) * 2 - 1)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
			&ABlackJack::DelayHit, 1, false);
		count++;
	}
	else
	{
		PlayerPoint = 0;
		count = 1;
		EndInitRound.Broadcast();
	}
}

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
	Sum = 0;
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


