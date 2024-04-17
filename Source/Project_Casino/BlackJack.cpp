// Fill out your copyright notice in the Description page of Project Settings.

#include <iostream>
#include <vector>
#include <algorithm>
#include "BlackJack.h"

void ABlackJack::InitGame()
{
	//���� ����
	//�÷��̾� �� ���� (ȥ�� ���� ���� ����ϰ� ������ ��� �߰�)
	//test��
	PlayerCount = 3;//�����ϴºκ� ui�� �����

	//�÷��̾� �� + 1 ��ŭ ����
	for (int i = 0; i < PlayerCount + 1; i++)
	{
		PlayerList.Push(PlayerInfo());
	}
	SetDeck();
}

// ���� ����
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
	//���� �ݾ� ���ϱ� �ڸ� ����
	InitRound();
}

void ABlackJack::Double()
{
	//���� ���� ������ ī�尡 �����̶�� ����Ǹ� ����
}

//���� �ʱ�ȭ
void ABlackJack::InitRound()
{
	for (PlayerPoint = 0; PlayerPoint < PlayerCount; PlayerPoint++)
		Hit();
	Hit();//ī�� �����ٶ� �޸�����

	for (PlayerPoint = 0; PlayerPoint < PlayerCount; PlayerPoint++)
		Hit();
	Hit();//��� �ո�����

	for (PlayerPoint = 0; PlayerPoint < PlayerCount; PlayerPoint++)
	{
		if(PlayerList[PlayerPoint].Hand[0].GetNum() == PlayerList[PlayerPoint].Hand[1].GetNum())
			UE_LOG(LogTemp, Warning, TEXT("%d Player  Double"), PlayerPoint);
	}
	PlayerPoint = 0;
}

void ABlackJack::DoubleDown()
{
	//���ñݾ� �ι�
	Hit();
	Stay();
}

void ABlackJack::Calc()
{
	if (!IsDealerTurn)
	{
		if (PlayerList[PlayerPoint].CalcSum() > 21)
		{
			UE_LOG(LogTemp, Warning, TEXT("%d Player Burst"), PlayerPoint);
			PlayerList[PlayerPoint].Sum = -1;
			Stay();
		}
	}
	else
		if (PlayerList[PlayerCount].CalcSum() < 16)
			Hit();
		else if (PlayerList[PlayerCount].CalcSum() > 21)
		{
			PlayerList[PlayerCount].Sum = 0;
			RoundEnd();
		}
		else
			RoundEnd();
}

int ABlackJack::GetPlayerPoint()
{
	return PlayerPoint;
}


void ABlackJack::RoundEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("RoundEnd"));	

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
			UE_LOG(LogTemp, Warning, TEXT("%d Player Draw"), i);//�Ǹ�ŭ
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("%d Player Loser"), i);//�Ǹ�ŭ
		if (Dealer == 21)
			return;//�ν��� * 2��
	}
	for (PlayerPoint = 0; PlayerPoint < PlayerCount+1; PlayerPoint++)
		PlayerList[PlayerPoint].Init();
	PlayerPoint = 0;
	IsDealerTurn = false;
	Bet();

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
}

void ABlackJack::Insurance()
{

}

void ABlackJack::Hit()
{
	Draw.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("%d Player  %d"), PlayerPoint, Deck[DeckPoint].GetNum());
	PlayerList[PlayerPoint].Hand.Push(Deck[DeckPoint++]);
	Calc();
}

void PlayerInfo::Init()
{
	Hand.Empty();
	Coin = 0;
	InsuranceCoin = 0;
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
	UE_LOG(LogTemp, Warning, TEXT("Player sum %d"),Sum); //UI�� �����ϱ�
	return Sum;
}
