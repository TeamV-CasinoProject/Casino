// Fill out your copyright notice in the Description page of Project Settings.


#include "CardInHands.h"
#include "Sevens.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
//#include "WidgetBlueprint.h"
#include "GameFramework/PlayerController.h"
#include "Async/Async.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Math/UnrealMathUtility.h"

ACardInHands::ACardInHands()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	IsClickable = true;
}

void ACardInHands::BeginPlay()
{
	if (Myself.GetNum() == 7)
	{
		SendCardToTable();
		ASevens::PlayerCards[PlayerNum]--;
		//Temp
		SevensGameMode->PlayerCardNum = ASevens::PlayerCards[0];
	}

	char Suit;
	switch (Myself.GetSuit())
	{
	case 0: Suit = 'S'; break;
	case 1: Suit = 'D'; break;
	case 2: Suit = 'H'; break;
	case 3: Suit = 'C'; break;
	}
	FString MeshPath = FString::Printf(TEXT("/Game/TS_LEGENO/CARD/FBX/%c%d"), Suit, Myself.GetNum());

	UStaticMesh* CardMesh = LoadObject<UStaticMesh>(nullptr, *MeshPath);
	if (CardMesh)
	{
		BaseMesh->SetStaticMesh(CardMesh);
		BaseMesh->SetWorldScale3D(FVector(1.15f, 0.9f, 1.0f));
	}
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
		--ASevens::PlayerCards[CurrentPlayerNum];
		//Temp
		SevensGameMode->PlayerCardNum = ASevens::PlayerCards[0];
		if (ASevens::PlayerCards[CurrentPlayerNum] == 0)
		{
			++SevensGameMode->RankStack;
			SevensGameMode->IsHasLost[CurrentPlayerNum] = 1;
			SevensGameMode->Ranking = SevensGameMode->RankStack;
			UE_LOG(LogTemp, Warning, TEXT("Player Win! [Ranking %d]"), SevensGameMode->RankStack);

			// Ending (Player 1st)
			SevensGameMode->endGame = true;
			return;
		}

		SendCardToTable();
		MoveToNextTurn();		

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
			&ACardInHands::TakeAITurn, Delay, false);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Can't Send"));
}

void ACardInHands::TakeAITurn()
{
	Delay = FMath::RandRange(0.6f, 2.0f);

	int CRN = ASevens::CurrentPlayerNum;
	if (1 <= CRN && CRN <= 3 && (SevensGameMode->IsHasLost[CRN] == 1 || SevensGameMode->IsHasLost[CRN] == -1))
	{
		if(SevensGameMode->IsHasLost[CRN] == 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("AI %d Waiting"), ASevens::CurrentPlayerNum);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AI %d Losed"), ASevens::CurrentPlayerNum);
		}

		MoveToNextTurn();
		if (ASevens::CurrentPlayerNum != 0)
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
				&ACardInHands::TakeAITurn, Delay, false);
		}
		return;
	}

	TArray<AActor*> FoundCards;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACardInHands::StaticClass(), FoundCards);

	for (AActor* Actor : FoundCards)
	{
		ACardInHands* Card = Cast<ACardInHands>(Actor);

		if (Card->GetPlayerNum() == ASevens::CurrentPlayerNum && Card->GetIsClickable())
		{	
			if (Card->CheckCardSendable())
			{
				--ASevens::PlayerCards[ASevens::CurrentPlayerNum];
				//Temp
				SevensGameMode->PlayerCardNum = ASevens::PlayerCards[0];
				UE_LOG(LogTemp, Warning, TEXT("AI %d Taked!"), ASevens::CurrentPlayerNum);

				if (ASevens::PlayerCards[ASevens::CurrentPlayerNum] == 0)
				{
					++SevensGameMode->RankStack;
					SevensGameMode->IsHasLost[ASevens::CurrentPlayerNum] = 1;
					UE_LOG(LogTemp, Warning, TEXT("AI %d Win! [Ranking %d]"), ASevens::CurrentPlayerNum, SevensGameMode->RankStack);
				}

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

				if (SevensGameMode->RankStack == 4)
				{
					// Ending (All AI is Ranked without Player)
					SevensGameMode->Ranking = SevensGameMode->RankStack;
					SevensGameMode->endGame = true;				
				}

				return;
			}
		}
	}

	//Print Test : Select Pass
	UE_LOG(LogTemp, Warning, TEXT("AI %d Passed..."), ASevens::CurrentPlayerNum);

	--ASevens::Passes[ASevens::CurrentPlayerNum];
	//Temp
	SevensGameMode->PlayerPassNum = ASevens::Passes[0];
	if (ASevens::Passes[ASevens::CurrentPlayerNum] < 0)
	{
		//Failed (AI Pass Zero)
		SevensGameMode->IsHasLost[ASevens::CurrentPlayerNum] = -1;
		
		TArray<AActor*> LoserCards;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACardInHands::StaticClass(), LoserCards);

		for (AActor* Actor : LoserCards)
		{
			ACardInHands* Card = Cast<ACardInHands>(Actor);

			if (Card->GetPlayerNum() == ASevens::CurrentPlayerNum && Card->GetIsClickable())
			{
				//UE_LOG(LogTemp, Warning, TEXT("LostLostLost %d"), Card->My);
				Card->SendCardToTable();

				if(Card->Myself.GetNum() > 7)
				{
					int Elt = Card->Myself.GetNum() * 10 + Card->Myself.GetSuit();
					SevensGameMode->LargeNumQueue.Add(Elt);
					UE_LOG(LogTemp, Warning, TEXT("Large"));
				}
				else
				{
					int Elt = -(Card->Myself.GetNum() * 10 + Card->Myself.GetSuit());
					SevensGameMode->LargeNumQueue.Add(Elt);
					UE_LOG(LogTemp, Warning, TEXT("Small"));
				}
			}
		}
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

		--ASevens::Passes[ASevens::CurrentPlayerNum];
		//Temp
		SevensGameMode->PlayerPassNum = ASevens::Passes[0];
		if (ASevens::Passes[ASevens::CurrentPlayerNum] < 0)
		{
			//Failed (Player Pass Zero)
			SevensGameMode->Ranking = 4;
			SevensGameMode->endGame = true;
			return;
		}

		MoveToNextTurn();

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

	SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
	SetActorLocation(FVector(150 - (Suit * 100), -450 + ((Num - 1) * 75), 520));

	IsClickable = false;
}

bool ACardInHands::CheckCardSendable()
{
	int Length = SevensGameMode->LargeNumQueue.Num();
	for (int i = 0; i < Length; i++)
	{
		int Elt = SevensGameMode->LargeNumQueue[i];
		SevensGameMode->LargeNumQueue.RemoveAt(i);
		if (Elt / 10 == (ASevens::Line[Elt % 10] % 100) + 1)
		{
			ASevens::Line[Elt % 10] += 1;
			continue;
		}
		SevensGameMode->LargeNumQueue.Add(Elt);
	}

	Length = SevensGameMode->SmallNumQueue.Num();
	for (int i = 0; i < Length; i++)
	{
		int Elt = SevensGameMode->SmallNumQueue[i] * -1;
		SevensGameMode->SmallNumQueue.RemoveAt(i);
		if (Elt / 10 == (ASevens::Line[Elt % 10] / 100) - 100)
		{
			ASevens::Line[Elt % 10] -= 100;
			continue;
		}
		SevensGameMode->SmallNumQueue.Add(Elt * -1);
	}

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
	//�� �� �ִ� ī�忡 ��ŷ ǥ��(�׵θ� ��, ��� ǥ�� ��)

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
