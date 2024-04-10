// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Card.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BlackJack.generated.h"

/**
 * 
 */

class PlayerInfo
{
public:
	TArray<Card> Hand;

	int Sum;
	int AceCount;
	void InitHand();
	void CalcSum();
private:
};

UCLASS()
class PROJECT_CASINO_API ABlackJack : public AGameModeBase
{
	GENERATED_BODY()
public:
	void InitGame(); // 게임 시작
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void SetDeck(); // 게임 시작하고 초기 덱 준비
	void InitRound(); // 딜러와 플레이어의 초기 카드 준비
	void Bet(); // 초기 배팅금액 설정
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void Hit();
	void DoubleDown();
	void Hit(PlayerInfo); //매개변수로 딜러, 플레이어를 받아 딜러/플레이어에게 카드 한장 줌

public:
	TArray<Card> Deck; //덱
	TArray<PlayerInfo> PlayerList; //혼자 1~3플레이어 하게되면 사용 0 : 딜러, 1~3 : 플레이어

	PlayerInfo p = PlayerInfo();
	int DeckPoint; //카드를 얼마나 썻나?
	int PlayerPoint; //누구턴인지 확인
	int Coin;// 배팅한 금액
};