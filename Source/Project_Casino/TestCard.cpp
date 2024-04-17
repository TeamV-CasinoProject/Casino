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

// Called when the game starts or when spawned
void ATestCard::BeginPlay()
{
	Super::BeginPlay();

	if (Text1)
	{
		//Text1->SetText(TEXT("")); // 텍스트 설정
		Text1->SetTextRenderColor(FColor::Black); // 텍스트 색상 설정
		//Text1->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center); // 수평 정렬 설정
		//Text1->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter); // 수직 정렬 설정
	}

	if (Text2)
	{
		//Text2->SetText(TEXT("")); // 텍스트 설정
		Text2->SetTextRenderColor(FColor::Black); // 텍스트 색상 설정
		//Text2->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center); // 수평 정렬 설정
		//Text2->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter); // 수직 정렬 설정
	}
}

// Called every frame
void ATestCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

