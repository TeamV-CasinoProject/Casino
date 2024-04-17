// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Card.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BlackJack.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDrawDeligate);


class PlayerInfo
{
public:
	TArray<Card> Hand;

	int Sum;
	int First;
	int Second;
	int Coin = 0;// ������ �ݾ�
	int InsuranceCoin = 0; //�����

	void Init();
	int CalcSum();
private:
};

UCLASS()
class PROJECT_CASINO_API ABlackJack : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void InitGame(); // ���� ����
	void SetDeck(); // ���� �����ϰ� �ʱ� �� �غ�
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void Bet(); // �ʱ� ���ñݾ� ����
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void Double();
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void InitRound(); // ����� �÷��̾��� �ʱ� ī�� �غ�
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void Hit();// ī�� ���� ��
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void Stay();// ������
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void Insurance(); 
	//����� ������ϰŶ� �����ɶ� ���ñݾ��� ���ݱ��� �������� �߰����� ������̸� ������� �ι� �ƴϸ� ���� ùī�尡 A�ƴϿ��� �����ϰ� �� ����
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void DoubleDown();// ���� ī�带 �ް� �� ���� �̱�� 2.5��
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	void Calc();//����Ʈ����, ����� ���� �������� Ȯ��
	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	int GetPlayerPoint();

	void Dealer();//����� ��
	void RoundEnd();//����� ���̳����� ���ñݾ� ����
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FDrawDeligate Draw;

	TArray<Card> Deck; //��
	TArray<PlayerInfo> PlayerList; // 0~2 : �÷��̾� ������ : ���

	int PlayerCount;//�÷��̾��� ��
	int DeckPoint; //ī�带 �󸶳� ����?
	int PlayerPoint; //���������� Ȯ��
	bool IsDealerTurn = false;
};