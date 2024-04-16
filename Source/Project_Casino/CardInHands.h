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
	//virtual void Tick(float DeltaTime) override;

protected:
	//virtual void BeginPlay() override;

public:		
	UFUNCTION()
	void OnCardClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);
	void SetSevensInstance(ASevens* PokerInstance);
	void SetMyself(int, int);

private:
	ASevens* Sevens;
	Card Myself;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CardMesh;
};
