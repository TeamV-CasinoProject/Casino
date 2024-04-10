// Fill out your copyright notice in the Description page of Project Settings.

#include <iostream>
#include <vector>
#include <algorithm>
#include "BlackJack.h"

void ABlackJack::InitGame()
{
	//설명 띄우기
	//플레이어 수 설정 (혼자 여러 덱을 사용하게 개발할 경우 추가)
	SetDeck();
}

// 게임 시작
void ABlackJack::SetDeck()
{
	for (int i = 0; i < 4; i++)
		for (int k = 1; k < 14; k++)
			for (int j = 0; j < 4; j++)
			{
				Card c(i, k);
				Deck.Push(Card(i, k));
				UE_LOG(LogTemp, Warning, TEXT("%d  %d"), c.Suit, c.Num);
			}
	

	for (int i = 0; i < 52*4 - 1; i++)
	{
		// `i <= j < n`이 되도록 난수 `j`를 생성하고
		// 인덱스 `j`에 있는 요소를 해당 요소로 교체합니다.
		// 현재 인덱스 `i`에 존재
		int j = i + rand() % (52*4 - i);
		std::swap(Deck[i], Deck[j]);
	}
}

void ABlackJack::Hit()
{
	UE_LOG(LogTemp, Warning, TEXT("%d  %d"), Deck[PlayerPoint].Suit, Deck[PlayerPoint].Num);
	p.Hand.Push(Deck[PlayerPoint++]);
	p.CalcSum();
}

void ABlackJack::DoubleDown()
{
	Hit();
	//배팅금액 낸만큼 더내기
	//Ai에게 턴넘기기
}

//void ABlackJack::Hit(PlayerInfo p)
//{
//	UE_LOG(LogTemp, Warning, TEXT("%s  %d"), Deck[PlayerPoint].Suit, Deck[PlayerPoint].Num);
//	p.Hand.Push(Deck[PlayerPoint++]);
//	p.CalcSum();
//}

 void PlayerInfo::CalcSum() {
	Sum = 0;
	for (auto It = Hand.begin(); It != Hand.end(); ++It)
	{
		Card Element = *It;
		if (Element.Num > 9)
			Sum += 10;
		else
			Sum += Element.Num;
		if (Element.Num == 1)
		{
			AceCount++;
			Sum += 10;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("sum %d"), Sum);
}
