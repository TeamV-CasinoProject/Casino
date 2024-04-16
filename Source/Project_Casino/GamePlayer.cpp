// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayer.h"

GamePlayer::GamePlayer()
{
	Pass = 5;
}

GamePlayer::~GamePlayer()
{
}

void GamePlayer::RemoveCardToHands(Card Selected)
{
	UE_LOG(LogTemp, Warning, TEXT("Proceed Turn..."));

	for (int i = 0; i < Hands.Num(); i++)
	{
		if (Hands[i].CheckEquality(Selected))
		{
			Hands.RemoveAt(i);
			break;
		}
	}

	//UpdateHands();
}

void GamePlayer::SetHands(TArray<Card> Deck, int Begin, int End)
{
	for (int i = Begin; i < End; i++)
	{
		Hands.Push(Deck[i]);
	}
}

TArray<Card>* GamePlayer::GetHands()
{
	return &Hands;
}

void GamePlayer::UpdateHands()
{
	//화면에 보여지는 패의 카드들을 정리(위치, 겹치는 정도 등)하는 코드
	//어쩌면 CardInHands 클래스 쪽에서 맡을지도
}
