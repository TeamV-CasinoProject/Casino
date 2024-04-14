// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayer.h"

GamePlayer::GamePlayer()
{
}

GamePlayer::GamePlayer(bool _IsActivated)
{
	IsActivated = _IsActivated;
}

GamePlayer::~GamePlayer()
{
}

void GamePlayer::TakeATurn()
{
	UE_LOG(LogTemp, Warning, TEXT("Proceed Turn..."));
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
	IsActivated = IsActivated ? false : true;
}
