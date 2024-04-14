// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class PROJECT_CASINO_API Card
{
public:
	Card();
	Card(int, int);
	~Card();

public:
	void PrintSuit();
	void SetCard(int , int);
	bool CheckEquality(Card);
	int GetSuit();
	int GetNum();

private:
	int Suit;
	int Num;
};
