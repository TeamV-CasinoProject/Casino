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
		void InitGame(); // ���� ����
		void SetDeck(); // ���� �����ϰ� �ʱ� �� �غ�
		void InitRound(); // ������ �÷��̾��� �ʱ� ī�� �غ�
		void Bet(); // �ʱ� ���ñݾ� ����
		void Hit(PlayerInfo); //�Ű������� ����, �÷��̾ �޾� ����/�÷��̾�� ī�� ���� ��

public:
	TArray<Card> Deck; //��
	TArray<PlayerInfo> PlayerList; //ȥ�� 1~3�÷��̾� �ϰԵǸ� ��� 0 : ����, 1~3 : �÷��̾�
	TArray<int>Sum;//�÷��̾� �� ���� 1~3 : 1~3�÷��̾�

	int DeckPoint; //ī�带 �󸶳� ����?
	int PlayerPoint; //���������� Ȯ��
	int Coin;// ������ �ݾ�
};
