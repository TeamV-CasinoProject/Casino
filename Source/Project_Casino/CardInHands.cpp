// Fill out your copyright notice in the Description page of Project Settings.


#include "CardInHands.h"
#include "Sevens.h"

ACardInHands::ACardInHands()
{
	//PrimaryActorTick.bCanEverTick = true;
}

ACardInHands::ACardInHands(Card _Myself)
{
	Myself = _Myself;
}

/*void ACardInHands::BeginPlay()
{
	Super::BeginPlay();	
}

void ACardInHands::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}*/

void ACardInHands::OnCardClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	if (Sevens)
		Sevens->TakeATurn(Myself);
}

void ACardInHands::SetSevensInstance(ASevens* SevensInstance)
{
	Sevens = SevensInstance;
}

void ACardInHands::SetMyself(int Suit, int Num)
{
	Myself.SetCard(Suit, Num);
}



