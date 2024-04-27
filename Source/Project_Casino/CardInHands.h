// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card.h"
#include "Components/TextRenderComponent.h"
#include "CardInHands.generated.h"

class ASevens;

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
	void SetMyself(int, int);
	void TakeATurn(int);
	void MoveToNextTurn();
	void SendCardToTable();
	bool CheckCardSendable();
	void MarkSendableCard();

private:
	Card Myself;
	bool IsClickable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UTextRenderComponent* TextComponent;
	
};
