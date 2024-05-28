// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SevensWinResult.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UUI_SevensWinResult::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// ���� �������Ʈ�� ��ư�� �̸��� ���� �����´�
	TestButton = Cast<UButton>(GetWidgetFromName(TEXT("TestButton")));

	// ���� �������Ʈ�� �ؽ�Ʈ ����� �̸��� ���� �����´�
	TestTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("TestTextBlock")));

	// ��ư Ŭ���� ȣ��� ��������Ʈ�� �Լ��� ����Ѵ�
	TestButton->OnClicked.AddDynamic(this, &UUI_SevensWinResult::TestButtonCallback);
}

void UUI_SevensWinResult::TestButtonCallback()
{
	// ��ư�� �������� ����� ���� ����
}