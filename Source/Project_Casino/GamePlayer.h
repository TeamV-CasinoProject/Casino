// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class PROJECT_CASINO_API GamePlayer
{
public:
	GamePlayer();

	~GamePlayer();

public:
	void TakeATurn();
	bool IsActive();
	void Activate();

private:
	bool IsActivated;
};
