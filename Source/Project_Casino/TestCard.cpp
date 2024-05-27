// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCard.h"
#include "Components/TextRenderComponent.h"


// Sets default values
ATestCard::ATestCard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComponent;


	Text1 = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text1"));
	Text1->SetupAttachment(RootComponent);

	Text2 = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text2"));
	Text2->SetupAttachment(RootComponent);

}

void ATestCard::Set(int num)
{
	FString TextString = FString::Printf(TEXT("%d"), num);
	FText Text = FText::FromString(TextString);
	if (Text1)
	{
		Text1->SetText(Text);
	}
	if(Text2)
	{
		Text2->SetText(Text);
	}
}



// Called when the game starts or when spawned
void ATestCard::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATestCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

