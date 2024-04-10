// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackJack.h"

void ABlackJack::InitGame()
{
	//설명 띄우기
	//플레이어 수 설정 (혼자 여러 덱을 사용하게 개발할 경우 추가)
	SetDeck();
}

// 게임 시작

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

