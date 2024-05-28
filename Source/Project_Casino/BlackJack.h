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
	TArray<UObject*>CardActor;
	int Sum;
	int First;
	int Second;
	int Coin = 0;// ������ �ݾ�
	int InsuranceCoin = 0; //�����

	void Init();
	int CalcSum();
private:
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChangePlayer);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndRound);

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
	void Calc();//����Ʈ����, ����� ���� �������� Ȯ��
	void AddCard(AActor* c);
	void SpawnCard();
	void UpdateUi();

	UFUNCTION(BlueprintCallable, Category = "BlackJack")
	int Getnum();

	void Dealer();//����� ��
	void RoundEnd();//����� ���̳����� ���ñݾ� ����
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FVector>CardPos;
	TArray<Card> Deck; //��
	TArray<PlayerInfo> PlayerList; // 0~2 : �÷��̾� ������ : ���

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int PlayerPoint; //���������� Ȯ�
	int PlayerCount;//�÷��̾��� ��
	int DeckPoint=0; //ī�带 �󸶳� ����?
	bool IsDealerTurn = false;
	TArray<FString> pscore;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString p1 = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString p2 = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString p3 = "";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString p4 = "";

	UPROPERTY(BlueprintAssignable)
	FChangePlayer ChangePlayerEvent;
	UPROPERTY(BlueprintAssignable)
	FEndRound EndRoundEvent;

	UFUNCTION(BlueprintCallable)
	void ChangePlayerEventTrigger()
	{
		ChangePlayerEvent.Broadcast();
	}
	void EndRoundEventTrigger()
	{
		EndRoundEvent.Broadcast();
	}
};