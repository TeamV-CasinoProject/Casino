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

	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponent"));
	TextComponent->SetupAttachment(RootComponent);

	IsClickable = true;
}

void ACardInHands::BeginPlay()
{
	if(Myself.GetNum() == 7)
		SendCardToTable();
	ASevens::Players2[Myself.GetNum()]--;

	FString Text = FString::Printf(TEXT("%d\n%d"), Myself.GetSuit(), Myself.GetNum());
	TextComponent->SetText(FText::FromString(Text));

	//TextComponent->AddLocalRotation(FRotator(0, 180, 0));
	TextComponent->SetWorldRotation(FRotator(0, 180, 0));
}

void ACardInHands::NotifyActorOnClicked(FKey ButtonPressed)
{
	UE_LOG(LogTemp, Warning, TEXT("Card is %d, %d"), Myself.GetSuit(), Myself.GetNum());

	if (IsClickable)
	{
		if (ASevens::CurrentPlayerNum == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("My Turns Started : %d"), ASevens::CurrentPlayerNum);
			TakeATurn(ASevens::CurrentPlayerNum);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AI Turns Started : %d"), ASevens::CurrentPlayerNum);
			TakeATurn(ASevens::CurrentPlayerNum);
		}
	}
}

void ACardInHands::SetMyself(int Suit, int Num)
{
	Myself.SetCard(Suit, Num);
}

void ACardInHands::TakeATurn(int Num)
{
	//ASevens::Players[Num].RemoveCardToHands(Myself);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), ASevens::Players.Num());

	if (CheckCardSendable())
	{
		ASevens::Players2[Num]--;

		SendCardToTable();
		MoveToNextTurn();

		if(ASevens::Players2[Num] == 0)
			UE_LOG(LogTemp, Warning, TEXT("Player%d Win!"), Num);
	}

	for (int i = 0; i < 4; i++)
		UE_LOG(LogTemp, Warning, TEXT("%d"), ASevens::Players2[i]);
}

void ACardInHands::MoveToNextTurn()
{
	ASevens::CurrentPlayerNum++;
	if (ASevens::CurrentPlayerNum == 4) ASevens::CurrentPlayerNum = 0;
}

void ACardInHands::SendCardToTable()
{
	UE_LOG(LogTemp, Warning, TEXT("DDD"));

	int Suit = Myself.GetSuit();
	int Num = Myself.GetNum();

	SetActorRotation(FRotator(0, 0, 0));
	SetActorLocation(FVector(150 - (Suit * 100), -450 + ((Num - 1) * 75), 300));

	IsClickable = false;
}

bool ACardInHands::CheckCardSendable()
{
	int Left = ASevens::Line[Myself.GetSuit()] / 100;
	int Right = ASevens::Line[Myself.GetSuit()] % 100;
	
	if (Myself.GetNum() == Left - 1)
	{
		ASevens::Line[Myself.GetSuit()] -= 100;
		return true;
	}
	
	if(Myself.GetNum() == Right + 1)
	{
		ASevens::Line[Myself.GetSuit()] += 1;
		return true;
	}

	return false;
}

void ACardInHands::MarkSendableCard()
{
	//낼 수 있는 카드에 마킹 표시(테두리 빛, 밝게 표시 등)ㄴ

	/*if (CheckCardSendable())
	{
		SetActorLocation(InitPoisition + FVector(0, 0, 100));
		return;
	}

	SetActorLocation(InitPoisition);*/	
}
