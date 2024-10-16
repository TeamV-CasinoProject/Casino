// Fill out your copyright notice in the Description page of Project Settings.


#include "OthelloPiece.h"

// Sets default values
AOthelloPiece::AOthelloPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOthelloPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOthelloPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOthelloPiece::FlipPiece()
{
	// 피스를 Y축 기준으로 180도 회전
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += 180.0f;
	SetActorRotation(NewRotation);
}

