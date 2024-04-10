// Fill out your copyright notice in the Description page of Project Settings.

#include <iostream>
#include <vector>
#include <algorithm>
#include "BlackJack.h"

void ABlackJack::InitGame()
{
	//���� ����
	//�÷��̾� �� ���� (ȥ�� ���� ���� ����ϰ� ������ ��� �߰�)
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
				UE_LOG(LogTemp, Warning, TEXT("%d  %d"), c.Suit, c.Num);
			}
	

	for (int i = 0; i < 52*4 - 1; i++)
	{
		// `i <= j < n`�� �ǵ��� ���� `j`�� �����ϰ�
		// �ε��� `j`�� �ִ� ��Ҹ� �ش� ��ҷ� ��ü�մϴ�.
		// ���� �ε��� `i`�� ����
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
	//���ñݾ� ����ŭ ������
	//Ai���� �ϳѱ��
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
