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

private:
	int Suit;
	int Num;
};
