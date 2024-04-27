// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.h"
#include "SevensPlayer.generated.h"

UCLASS()
class PROJECT_CASINO_API USevensPlayer : public UObject
{
	GENERATED_BODY()
	
public:
	USevensPlayer();

public:
	void RemoveCardToHands(Card);
	void SetHands(TArray<Card>, int, int);
	TArray<Card>* GetHands();
	void UpdateHands();

private:
	TArray<Card> Hands;
	int Pass;
};
