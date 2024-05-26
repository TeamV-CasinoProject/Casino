// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card.h"
#include "Components/TextRenderComponent.h"
#include "CardInHands.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameWinDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameLoseDelegate);
class ASevens;

UCLASS()
class PROJECT_CASINO_API ACardInHands : public AActor
{ 
	GENERATED_BODY()
	
public:	
	ACardInHands();
	virtual void BeginPlay() override;
	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

protected:

public:		
	void TakePlayerTurn(int);
	void TakeAITurn();
	UFUNCTION(BlueprintCallable)
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
	
	UPROPERTY(BlueprintAssignable, Category = "SevensValues")
	FGameWinDelegate GameWinEvent;
	UPROPERTY(BlueprintAssignable, Category = "SevensValues")
	FGameLoseDelegate GameLoseEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool endGame = false;

	ASevens* SevensGameMode;
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
