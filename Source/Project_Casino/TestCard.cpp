// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCard.h"
#include "Components/TextRenderComponent.h"


// Sets default values
ATestCard::ATestCard()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	UStaticMesh* CardMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/shuby/Meshes/CardMesh"));
	if (CardMesh)
	{
		BaseMesh->SetStaticMesh(CardMesh);
		BaseMesh->SetWorldScale3D(FVector(0.2f,0.2f, 0.01f));

		UMaterial* CardMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Game/shuby/Materials/CardDesign/M_Back"));
		if (CardMaterial)
		{
			BaseMesh->SetMaterial(0, CardMaterial);
		}
	}

	PlaneComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane Component"));
	PlaneComponent->SetupAttachment(RootComponent);
}

void ATestCard::Set(int _num,int _suit)
{
	num = _num;
	suit = _suit;

	UStaticMesh* PlaneMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Plane"));
	if (PlaneMesh)
	{
		PlaneComponent->SetStaticMesh(PlaneMesh);

		PlaneComponent->SetRelativeLocation(FVector(0.0f, -0.5f, -0.1f));
		PlaneComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 180.0f));
		PlaneComponent->SetRelativeScale3D(FVector(0.65f, 0.9f, 1.0f));

		int32 MaterialNum = suit * 13 + num;
		FString MaterialPath = FString::Printf(TEXT("/Game/shuby/Materials/CardDesign/M_Front%d"), MaterialNum);
		UMaterial* CardMaterial2 = LoadObject<UMaterial>(nullptr, *MaterialPath);
		if (CardMaterial2)
		{
			PlaneComponent->SetMaterial(0, CardMaterial2);
		}
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

