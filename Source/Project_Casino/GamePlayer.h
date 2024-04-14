// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Card.h"
#include "CoreMinimal.h"

class PROJECT_CASINO_API GamePlayer
{
public:
	GamePlayer();
	GamePlayer(bool);
	~GamePlayer();

public:
	void TakeATurn();
	void SetHands(TArray<Card>, int , int);
	bool IsActive();
	void Activate();
	void Deactivate();
	void RemoveCard();

private:
	TArray<Card> Hands;	
	bool IsActivated;
	int Pass;
};
