// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SevensWinResult.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UUI_SevensWinResult::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// 위젯 블루프린트의 버튼을 이름을 통해 가져온다
	TestButton = Cast<UButton>(GetWidgetFromName(TEXT("TestButton")));

	// 위젯 블루프린트의 텍스트 블록을 이름을 통해 가져온다
	TestTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("TestTextBlock")));

	// 버튼 클릭시 호출될 델리게이트에 함수를 등록한다
	TestButton->OnClicked.AddDynamic(this, &UUI_SevensWinResult::TestButtonCallback);
}

void UUI_SevensWinResult::TestButtonCallback()
{
	// 버튼이 눌렸을때 실행될 내용 구현
}