// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackJack.h"

void ABlackJack::InitGame()
{
	//���� ����
	//�÷��̾� �� ���� (ȥ�� ���� ���� ����ϰ� ������ ��� �߰�)
	SetDeck();
}

// ���� ����

inline void ABlackJack::SetDeck()
{
	for (int i = 0; i < 4; i++)
		for (int k = 1; k < 14; k++)
			for (int j = 0; j < 4; j++)
			{
				Card c(i, k);
				Deck.Push(Card(i, k));
			}
}

void ABlackJack::InitRound()
{

}

void ABlackJack::Bet()
{
	
}

void ABlackJack::Hit(PlayerInfo p)
{
	p.Hand.Push(Deck[PlayerPoint++]);
	p.CalcSum();
}

