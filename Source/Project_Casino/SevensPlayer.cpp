// Fill out your copyright notice in the Description page of Project Settings.


#include "SevensPlayer.h"

USevensPlayer::USevensPlayer()
{
	Pass = 5;
}

void USevensPlayer::RemoveCardToHands(Card Selected)
{
	for (int i = 0; i < Hands.Num(); i++)
	{
		if (Hands[i].CheckEquality(Selected))
		{
			Hands.RemoveAt(i);
			break;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("-- Remaining Cards -- : %d"), Hands.Num());
	for (int i = 0; i < Hands.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d, %d"), Hands[i].GetSuit(), Hands[i].GetNum());
	}
	//UpdateHands();
}

void USevensPlayer::SetHands(TArray<Card> Deck, int Begin, int End)
{
	for (int i = Begin; i < End; i++)
	{
		Hands.Push(Deck[i]);
	}
}

TArray<Card>* USevensPlayer::GetHands()
{
	return &Hands;
}

void USevensPlayer::UpdateHands()
{
	//ȭ�鿡 �������� ���� ī����� ����(��ġ, ��ġ�� ���� ��)�ϴ� �ڵ�
	//��¼�� CardInHands Ŭ���� �ʿ��� ��������


}