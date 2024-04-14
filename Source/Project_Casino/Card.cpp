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

void Card::SetCard(int _Suit, int _Num)
{
	Suit = _Suit;
	Num = _Num;
}

bool Card::CheckEquality(Card Another)
{
	if(Suit == Another.Suit && Num == Another.Num)
		return true;

	return false;
}

int Card::GetSuit()
{
	return Suit;
}

int Card::GetNum()
{
	return Num;
}
