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

	BaseMesh->OnClicked.AddDynamic(this, &ACardInHands::ActorOnClicked);
}

ACardInHands::ACardInHands(Card _Myself)
{
	Myself = _Myself;
}

void ACardInHands::BeginPlay()
{
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BaseMesh->SetVisibility(true);
	
}

void ACardInHands::ActorOnClicked(UPrimitiveComponent* TouchedActor, FKey ButtonPressed)
{
	UE_LOG(LogTemp, Warning, TEXT("finally 22..."));
	/*if (Sevens)
		Sevens->TakeATurn(Myself);*/
}

void ACardInHands::SetSevensInstance(ASevens* SevensInstance)
{
	Sevens = SevensInstance;
}

void ACardInHands::SetMyself(int Suit, int Num)
{
	Myself.SetCard(Suit, Num);
}



