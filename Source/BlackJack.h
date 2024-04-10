// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include<iostream>
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

	void InitHand();
	void CalcSum();
		
private:
	int Sum;
};

class PROJECT_CASINO_API ABlackJack : public AGameModeBase
{
	public:
		void InitGame(); // 게임 시작
		void SetDeck(); // 게임 시작하고 초기 덱 준비
		void InitRound(); // 딜러와 플레이어의 초기 카드 준비
		void Bet(); // 초기 배팅금액 설정
		void Hit(PlayerInfo); //매개변수로 딜러, 플레이어를 받아 딜러/플레이어에게 카드 한장 줌

public:
	TArray<Card> Deck; //덱
	TArray<PlayerInfo> PlayerList; //혼자 1~3플레이어 하게되면 사용 0 : 딜러, 1~3 : 플레이어
	TArray<int>Sum;//플레이어 별 점수 1~3 : 1~3플레이어

	int DeckPoint; //카드를 얼마나 썻나?
	int PlayerPoint; //누구턴인지 확인
	int Coin;// 배팅한 금액
};
