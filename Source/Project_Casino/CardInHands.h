// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card.h"
#include "Components/TextRenderComponent.h"
#include "CardInHands.generated.h"

class ASevens;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameEndDelegate);
//static const int Delay = 1.3f;

UCLASS()
class PROJECT_CASINO_API ACardInHands : public AActor
{ 
	GENERATED_BODY()
	
public:	
	ACardInHands();
	virtual void BeginPlay() override;

protected:
	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

public:		
	void TakePlayerTurn(int);
	void TakeAITurn();
	UFUNCTION(BlueprintCallable, Category = "SevensValues")
	void PassTurn();
	void MoveToNextTurn();
	void SendCardToTable();
	bool CheckCardSendable();
	void MarkSendableCard();
	void SetMyself(int, int);
	int GetMyself();
	void SetPlayerNum(int);
	int GetPlayerNum();
	bool GetIsClickable();
	void BroadcastGameEnd();

	UPROPERTY(BlueprintAssignable, Category = "SevensValues")
	FGameEndDelegate GameWinEvent;
	UPROPERTY(BlueprintAssignable, Category = "SevensValues")
	FGameEndDelegate GameLoseEvent;

private:
	Card Myself;
	bool IsClickable;
	int PlayerNum;
	float Delay = 0.3f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UTextRenderComponent* TextComponent;

	FTimerHandle TimerHandle;	
};
