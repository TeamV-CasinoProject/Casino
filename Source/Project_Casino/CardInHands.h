// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card.h"
#include "CardInHands.generated.h"

class ASevens;

UCLASS()
class PROJECT_CASINO_API ACardInHands : public AActor
{
	GENERATED_BODY()
	
public:	
	ACardInHands();
	ACardInHands(Card);
	virtual void BeginPlay() override;

protected:
	void OnActorClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

public:		
	UFUNCTION()
	void SetSevensInstance(ASevens* PokerInstance);
	void SetMyself(int, int);

private:
	ASevens* Sevens;
	Card Myself;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	class UInputComponent* InputComponent;
};
