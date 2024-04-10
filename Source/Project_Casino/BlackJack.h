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
	void InitGame(); // ���� ����
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void SetDeck(); // ���� �����ϰ� �ʱ� �� �غ�
	void InitRound(); // ������ �÷��̾��� �ʱ� ī�� �غ�
	void Bet(); // �ʱ� ���ñݾ� ����
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void Hit();
	void DoubleDown();
	void Hit(PlayerInfo); //�Ű������� ����, �÷��̾ �޾� ����/�÷��̾�� ī�� ���� ��

public:
	TArray<Card> Deck; //��
	TArray<PlayerInfo> PlayerList; //ȥ�� 1~3�÷��̾� �ϰԵǸ� ��� 0 : ����, 1~3 : �÷��̾�

	PlayerInfo p = PlayerInfo();
	int DeckPoint; //ī�带 �󸶳� ����?
	int PlayerPoint; //���������� Ȯ��
	int Coin;// ������ �ݾ�
};