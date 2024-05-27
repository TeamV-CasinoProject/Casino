// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestCard.generated.h"

class UTextRenderComponent;

UCLASS()
class PROJECT_CASINO_API ATestCard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestCard();
	UFUNCTION(BlueprintCallable, Category = "Card")
	void Set(int i);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UTextRenderComponent* Text1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* Text2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComponent;

};
