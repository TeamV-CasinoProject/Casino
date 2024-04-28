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
	UE_LOG(LogTemp, Warning, TEXT("Card is %d, %d"), Myself.GetSuit(), Myself.GetNum());

	//플레이어의 턴일 때만 동작하도록 수정(PlayerNum 이용해서 PlayerNum이 0인 경우에만 동작하도록)
	if (IsClickable)
	{
		if (ASevens::CurrentPlayerNum == 0 && PlayerNum == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("My Turns Started : %d"), ASevens::CurrentPlayerNum);
			TakePlayerTurn(ASevens::CurrentPlayerNum);
		}
	}
}

void ACardInHands::TakePlayerTurn(int Num)
{
	//ASevens::Players[Num].RemoveCardToHands(Myself);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), ASevens::Players.Num());

	if (CheckCardSendable())
	{
		ASevens::PlayerCards[Num]--;

		SendCardToTable();
		MoveToNextTurn();

		/*if(ASevens::PlayerCards[Num] == 0)
			UE_LOG(LogTemp, Warning, TEXT("Player%d Win!"), Num);*/

		float Delay = 2.0f;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
			&ACardInHands::TakeAITurn, Delay, false);

		//Print Test : Number of Cards Remaining 
		for (int i = 0; i < 4; i++)
			UE_LOG(LogTemp, Warning, TEXT("%d"), ASevens::PlayerCards[i]);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Can't Send"));
}

void ACardInHands::TakeAITurn()
{
	TArray<AActor*> FoundCards;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACardInHands::StaticClass(), FoundCards);

	float Delay = 2.0f;

	for (AActor* Actor : FoundCards)
	{
		ACardInHands* Card = Cast<ACardInHands>(Actor);

		if (Card->GetPlayerNum() == ASevens::CurrentPlayerNum && Card->GetIsClickable())
		{
			//Print Test : Current Turn Player's Cards
			//UE_LOG(LogTemp, Warning, TEXT("Num: %d / AI: %d"), Card->GetPlayerNum(), Card->GetMyself());			

			if (Card->CheckCardSendable())
			{
				ASevens::PlayerCards[ASevens::CurrentPlayerNum]--;

				UE_LOG(LogTemp, Warning, TEXT("AI %d Taked!"), ASevens::CurrentPlayerNum);

				Card->SendCardToTable();
				Card->MoveToNextTurn();

				/*if(ASevens::PlayerCards[Num] == 0)
					UE_LOG(LogTemp, Warning, TEXT("Player%d Win!"), Num);*/				

				if(ASevens::CurrentPlayerNum != 0)
				{					
					GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
						&ACardInHands::TakeAITurn, Delay, false);
				}
				return;
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("AI %d Busted..."), ASevens::CurrentPlayerNum);
	MoveToNextTurn();	
	if (ASevens::CurrentPlayerNum != 0)
	{
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
