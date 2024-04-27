// Fill out your copyright notice in the Description page of Project Settings.


#include "CardInHands.h"
#include "Sevens.h"

ACardInHands::ACardInHands()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	UStaticMesh* CardMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/shuby/CardMesh"));
	if (CardMesh)
	{
		BaseMesh->SetStaticMesh(CardMesh);

		BaseMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
}

void ACardInHands::BeginPlay()
{
	
}

void ACardInHands::NotifyActorOnClicked(FKey ButtonPressed)
{
	UE_LOG(LogTemp, Warning, TEXT("Card is %d, %d"), Myself.GetSuit(), Myself.GetNum());
	if (ASevens::CurrentPlayerNum == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("My Turns Started : %d"), ASevens::CurrentPlayerNum);
		TakeATurn();		
	}		
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Turns Started : %d"), ASevens::CurrentPlayerNum);
		TakeATurn();
	}

	if (DestroyButton == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("DDD"));
		ACardInHands::Destroy();
	}
}

void ACardInHands::SetMyself(int Suit, int Num)
{
	Myself.SetCard(Suit, Num);
}

void ACardInHands::TakeATurn()
{
	//ASevens::Players[ASevens::CurrentPlayerNum].RemoveCardToHands(Myself);
	//PlayCard();
	MoveToNextTurn();

	DestroyButton = 1;
}

void ACardInHands::MoveToNextTurn()
{
	ASevens::CurrentPlayerNum++;
	if (ASevens::CurrentPlayerNum == 4) ASevens::CurrentPlayerNum = 0;
}