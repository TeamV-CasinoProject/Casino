// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	ShowMouseCursor(true);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();	

	SetActorLocation(FVector(-1100, 0, 1440));
	SetActorRotation(FRotator(0, 0, 5));
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerPawn::ShowMouseCursor(bool bShowCursor)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = bShowCursor;
	}
}