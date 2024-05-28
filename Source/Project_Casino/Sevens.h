// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Math/UnrealMathUtility.h"
#include "CardInHands.h"
#include "Containers/Queue.h"
#include "Containers/Array.h"
#include "Engine/World.h"
#include "Sevens.generated.h"

class Card;

static const int PlayerNum = 4;
static const int SuitNum = 4;

UCLASS()
class PROJECT_CASINO_API ASevens : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASevens();

protected:
	virtual void BeginPlay() override;

public:
	void SetGame();
	void ShuffleDeck(TArray<Card>&);
	void SpawnCard(FVector, FRotator, FActorSpawnParameters, Card, int);

	static int CurrentPlayerNum;
	static int PlayerCards[PlayerNum];
	static int Passes[PlayerNum];
	static int Line[SuitNum];

	int IsHasLost[PlayerNum];

	TArray<int32> LargeNumQueue;
	TArray<int32> SmallNumQueue;
	/*std::priority_queue<int> LargeNumQueue;
	std::priority_queue<int> SmallNumQueue;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int RankStack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Ranking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool endGame;

	//I finally found a way to connect with 'Sevens', 
	//so later I change all the 'static' values and change the approach on the card
	
private:
	TArray<Card> Deck;
};

int ASevens::CurrentPlayerNum = 0;
int ASevens::PlayerCards[PlayerNum]{ 0, 0, 0, 0 };
int ASevens::Passes[PlayerNum]{ 0, 0, 0, 0 };
int ASevens::Line[SuitNum]{ 0, 0, 0, 0 };