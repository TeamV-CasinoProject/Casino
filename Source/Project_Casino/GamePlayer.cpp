// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayer.h"

GamePlayer::GamePlayer()
{
	Pass = 5;
}

GamePlayer::GamePlayer(bool _IsActivated)
{
	Pass = 5;
	IsActivated = _IsActivated;
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

bool GamePlayer::IsActive()
{
	return IsActivated;
}

void GamePlayer::Activate()
{
	IsActivated = true;
}

void GamePlayer::Deactivate()
{
	IsActivated = false;
}

void GamePlayer::UpdateHands()
{
	//ȭ�鿡 �������� ���� ī����� ����(��ġ, ��ġ�� ���� ��)�ϴ� �ڵ�
	//��¼�� CardInHands Ŭ���� �ʿ��� ��������
}
