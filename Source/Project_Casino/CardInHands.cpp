// Fill out your copyright notice in the Description page of Project Settings.


#include "CardInHands.h"
#include "Sevens.h"
#include "Kismet/GameplayStatics.h"
#include "Async/Async.h"
#include "TimerManager.h"

ACardInHands::ACardInHands()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	UStaticMesh* CardMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/shuby/Meshes/CardMesh"));
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
	if (Myself.GetNum() == 7)
	{
		SendCardToTable();
		ASevens::PlayerCards[PlayerNum]--;
	}
	 
	FString Text = FString::Printf(TEXT("%d\n%d"), Myself.GetSuit(), Myself.GetNum());
	TextComponent->SetText(FText::FromString(Text));

	TextComponent->SetWorldRotation(FRotator(0, 180, 0));
}

void ACardInHands::NotifyActorOnClicked(FKey ButtonPressed)
{
	//Print Test : Selected Card Data
	UE_LOG(LogTemp, Warning, TEXT("-------------------------------"));
	UE_LOG(LogTemp, Warning, TEXT("Card is %d, %d"), Myself.GetSuit(), Myself.GetNum());

	if (IsClickable)
	{
		if (ASevens::CurrentPlayerNum == 0 && PlayerNum == 0)
		{
			TakePlayerTurn(ASevens::CurrentPlayerNum);
		}
	}
}

void ACardInHands::TakePlayerTurn(int CurrentPlayerNum)
{
	if (CheckCardSendable())
	{
		ASevens::PlayerCards[CurrentPlayerNum]--;

		if (ASevens::PlayerCards[CurrentPlayerNum] == 0)
			UE_LOG(LogTemp, Warning, TEXT("Player Win! Rank is ?"));

		SendCardToTable();
		MoveToNextTurn();		

		float Delay = 1.3f;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
			&ACardInHands::TakeAITurn, Delay, false);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Can't Send"));
}

void ACardInHands::TakeAITurn()
{
	TArray<AActor*> FoundCards;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACardInHands::StaticClass(), FoundCards);

	float Delay = 1.3f;

	for (AActor* Actor : FoundCards)
	{
		ACardInHands* Card = Cast<ACardInHands>(Actor);

		if (Card->GetPlayerNum() == ASevens::CurrentPlayerNum && Card->GetIsClickable())
		{	
			if (Card->CheckCardSendable())
			{
				ASevens::PlayerCards[ASevens::CurrentPlayerNum]--;

				UE_LOG(LogTemp, Warning, TEXT("AI %d Taked!"), ASevens::CurrentPlayerNum);

				if (ASevens::PlayerCards[ASevens::CurrentPlayerNum] == 0)
					UE_LOG(LogTemp, Warning, TEXT("AI %d Win! Rank is ?"), ASevens::CurrentPlayerNum);

				Card->SendCardToTable();
				Card->MoveToNextTurn();				

				if(ASevens::CurrentPlayerNum != 0)
				{					
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
						&ACardInHands::TakeAITurn, Delay, false);
				}
				else
				{
					//Print Test : Number of Cards Remaining 
					for (int i = 0; i < 4; i++)
						UE_LOG(LogTemp, Warning, TEXT("Remain: %d"), ASevens::PlayerCards[i]);

					//Print Test : Number of Cards Remaining 
					for (int i = 0; i < 4; i++)
						UE_LOG(LogTemp, Warning, TEXT("Pass: %d"), ASevens::Passes[i]);
				}

				return;
			}
		}
	}

	//Print Test : Select Pass
	UE_LOG(LogTemp, Warning, TEXT("AI %d Passed..."), ASevens::CurrentPlayerNum);

	ASevens::Passes[ASevens::CurrentPlayerNum]--;
	if (ASevens::Passes[ASevens::CurrentPlayerNum] < 0)
	{
		//패스 전부 소모해서 사망
	}

	MoveToNextTurn();	
	if (ASevens::CurrentPlayerNum != 0)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
			&ACardInHands::TakeAITurn, Delay, false);
	}
	else
	{
		//Print Test : Number of Cards Remaining 
		for (int i = 0; i < 4; i++)
			UE_LOG(LogTemp, Warning, TEXT("Remain: %d"), ASevens::PlayerCards[i]);

		//Print Test : Number of Cards Remaining 
		for (int i = 0; i < 4; i++)
			UE_LOG(LogTemp, Warning, TEXT("Pass: %d"), ASevens::Passes[i]);
	}
}

void ACardInHands::PassTurn()
{
	if (ASevens::CurrentPlayerNum == 0)
	{
		//Print Test : Select Pass
		UE_LOG(LogTemp, Warning, TEXT("-------------------------------"));
		UE_LOG(LogTemp, Warning, TEXT("Passed~"));

		ASevens::Passes[ASevens::CurrentPlayerNum]--;
		if (ASevens::Passes[ASevens::CurrentPlayerNum] < 0)
		{
			//패스 전부 소모해서 사망
		}

		MoveToNextTurn();

		float Delay = 1.3f;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
			&ACardInHands::TakeAITurn, Delay, false);
	}	
}

void ACardInHands::MoveToNextTurn()
{
	ASevens::CurrentPlayerNum++;
	if (ASevens::CurrentPlayerNum == 4) ASevens::CurrentPlayerNum = 0;
}

void ACardInHands::SendCardToTable()
{
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
	//낼 수 있는 카드에 마킹 표시(테두리 빛, 밝게 표시 등)

	/*if (CheckCardSendable())
	{
		SetActorLocation(InitPoisition + FVector(0, 0, 100));
		return;
	}

	SetActorLocation(InitPoisition);*/	
}

void ACardInHands::SetMyself(int Suit, int Num)
{
	Myself.SetCard(Suit, Num);
}

int ACardInHands::GetMyself()
{
	return Myself.GetSuit() * 100 + Myself.GetNum();
}

void ACardInHands::SetPlayerNum(int _PlayerNum)
{
	PlayerNum = _PlayerNum;
}

int ACardInHands::GetPlayerNum()
{
	return PlayerNum;
}

bool ACardInHands::GetIsClickable()
{
	return IsClickable;
}