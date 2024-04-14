// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"

Card::Card()
{
}

Card::Card(int _Suit, int _Num)
{
	Suit = _Suit;
	Num = _Num;
}

Card::~Card()
{
}

void Card::PrintSuit()
{
	UE_LOG(LogTemp, Warning, TEXT("Suit is %d %d"), Suit, Num);
}

bool Card::CheckEquality(Card Another)
{
	if(Suit == Another.Suit && Num == Another.Num)
		return true;

	return false;
}
