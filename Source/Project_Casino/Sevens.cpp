// Fill out your copyright notice in the Description page of Project Settings.


#include "Sevens.h"
#include "Card.h"

ASevens::ASevens()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASevens::BeginPlay()
{
	Super::BeginPlay();
	SetPlayers();
	SetGame();

	CurrentPlayerNum = 0;
	TurnProcess = 0;

	TmpTime = 0;
}
/*
void ASevens::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (TurnProcess)
	{
	case 0:
		if (!Players[CurrentPlayerNum].IsActive())
			Players[CurrentPlayerNum].Activate();
		TurnProcess = 1;
		break;

	case 1:
		TurnProcess = 2;
		TurnProcess = Players[CurrentPlayerNum].TakeATurn();		
		break;

	case 3:
		Players[CurrentPlayerNum].Deactivate();
		CurrentPlayerNum++;
		if (CurrentPlayerNum == 4) CurrentPlayerNum = 0;
		Players[CurrentPlayerNum].Activate();
		break;
	}
	
}
*/

/*
if (!Players[CurrentPlayerNum].IsActive())
			Players[CurrentPlayerNum].Activate();

if(TmpTime > 2.0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d has "), CurrentPlayerNum);
		//Players[CurrentPlayerNum].TakeATurn();

		Players[CurrentPlayerNum].Deactivate();
		CurrentPlayerNum++;
		if (CurrentPlayerNum == 4) CurrentPlayerNum = 0;
		Players[CurrentPlayerNum].Activate();

		TmpTime = 0;
	}

	TmpTime += DeltaTime;
*/

void ASevens::SetGame()
{
	//Reset Card
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j <= 13; j++)
		{	
			Deck.Push(Card(i, j));
		}
	}

	//Shuffle Card
	ShuffleDeck(Deck);

	//Print Test
	for (int i = 0; i < Deck.Num(); i++)
	{
		Deck[i].PrintSuit();
	}

	//Hand Out Cards to Players
	for (int i = 0; i < PlayerNum; i++)
	{
		Players[i].SetHands(Deck, i * 13, (i + 1) * 13);
	}

	//패에 있는 카드를 화면에 나열하는 코드
	for (int i = 0; i < PlayerNum; i++)
	{
		TArray<Card> Hands = *(Players[i].GetHands());
		for (int j = 0; j < Hands.Num(); j++)
		{
			FVector SpawnLocation = FVector(i * 70, j * 50, 400);
			SpawnCard(SpawnLocation, FRotator(), FActorSpawnParameters(), Hands[i]);
		}
	}
}

void ASevens::SetPlayers()
{
	for (int i = 0; i < PlayerNum; i++)
	{
		Players.Push(GamePlayer());
	}
}

void ASevens::ShuffleDeck(TArray<Card>& _Deck)
{
	int DeckSize = _Deck.Num();
	for (int i = 0; i < DeckSize; i++)
	{
		int RandomIdx = FMath::RandRange(0, DeckSize - 1);

		Card Tmp = _Deck[i];
		_Deck[i] = _Deck[RandomIdx];
		_Deck[RandomIdx] = Tmp;
	}
}

void ASevens::TakeATurn(Card Selected)
{
	Players[CurrentPlayerNum].RemoveCardToHands(Selected);

	//PlayCard();
	MoveToNextTurn();
}

void ASevens::SpawnCard(FVector SpawnLocation, FRotator Rotator, FActorSpawnParameters SpawnParams, Card _Card)
{
	ACardInHands* NewCard = GetWorld()->SpawnActor<ACardInHands>(
		ACardInHands::StaticClass(), SpawnLocation, Rotator, SpawnParams);

	NewCard->SetMyself(_Card.GetSuit(), _Card.GetNum());

	UStaticMeshComponent* MeshComponent = NewObject<UStaticMeshComponent>(NewCard);
	UE_LOG(LogTemp, Warning, TEXT("Card Spawned"));
	UStaticMesh* CubeMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (CubeMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("Mesh Spawned"));
		MeshComponent->SetStaticMesh(CubeMesh);

		UMaterial* BasicShapeMaterial = LoadObject<UMaterial>(nullptr, TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
		if (BasicShapeMaterial)
		{
			MeshComponent->SetMaterial(0, BasicShapeMaterial);
		}

		MeshComponent->SetWorldScale3D(FVector(0.9f, 0.65f, 0.01f));

		MeshComponent->AttachToComponent(NewCard->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

		MeshComponent->SetWorldLocationAndRotation(SpawnLocation, Rotator);
	}
}

void ASevens::MoveToNextTurn()
{
	CurrentPlayerNum++;
	if (CurrentPlayerNum == 4) CurrentPlayerNum = 0;
}

void ASevens::PlayCard()
{
	//카드를 내는 작업 - 실제 카드 인스턴스를 생성하고 화면의 적절한 위치로 이동
}
