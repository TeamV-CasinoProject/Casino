// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_SevensWinResult.generated.h"

UCLASS()
class PROJECT_CASINO_API UUI_SevensWinResult : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* TestButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* TestTextBlock;

protected:
	virtual void NativeOnInitialized();

private:
	// ��ư�� ������ ��, ȣ��� ��������Ʈ�� ����� �Լ�
	UFUNCTION(BlueprintCallable)
	void TestButtonCallback();
};
