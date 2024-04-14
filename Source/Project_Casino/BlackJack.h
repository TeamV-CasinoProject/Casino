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
	int First;
	int Second;
	void InitHand();
	int CalcSum();
	int Coin = 0;// 배팅한 금액
	int InsuranceCoin = 0; //보험금
private:
};

UCLASS()
class PROJECT_CASINO_API ABlackJack : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void InitGame(); // 게임 시작
	void SetDeck(); // 게임 시작하고 초기 덱 준비
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void Bet(); // 초기 배팅금액 설정
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void Double();
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void InitRound(); // 딜러와 플레이어의 초기 카드 준비
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void Hit();// 카드 한장 더
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void Stay();// 턴종료
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void Insurance(); 
	//딜러가 블랙잭일거라 생각될때 배팅금액의 절반까지 보험으로 추가지불 블랙잭이면 보험금의 두배 아니면 증발 첫카드가 A아니여도 가능하게 룰 수정
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void DoubleDown();// 다음 카드를 받고 턴 종료 이기면 2.5배
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void Calc();//버스트인지, 딜러의 턴이 끝났는지 확인

	void Dealer();//딜러의 턴
	void RoundEnd();//딜러의 턴이끝나고 배팅금액 정산
public:
	TArray<Card> Deck; //덱
	TArray<PlayerInfo> PlayerList; // 0~2 : 플레이어 마지막 : 딜러

	int PlayerCount;//플레이어의 수
	int DeckPoint; //카드를 얼마나 썻나?
	int PlayerPoint; //누구턴인지 확인
	bool IsDealerTurn = false;
};