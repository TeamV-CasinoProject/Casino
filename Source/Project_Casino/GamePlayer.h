// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Card.h"
#include "CoreMinimal.h"

static class PROJECT_CASINO_API GamePlayer
{
public:
	GamePlayer();
	~GamePlayer();

public:
	void RemoveCardToHands(Card);
	void SetHands(TArray<Card>, int , int);
	TArray<Card>* GetHands();
	void UpdateHands();

private:
	TArray<Card> Hands;	
	int Pass;
};
