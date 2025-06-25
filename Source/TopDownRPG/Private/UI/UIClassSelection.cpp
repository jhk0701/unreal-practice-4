// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIClassSelection.h"

#include "InGame/Title/TitleGameState.h"


void UUIClassSelection::InitClassList()
{
	// TODO : 캐릭터 정보 리스트에서 정보 출력



	SelectClass(0); // 첫번째 클래스 선택
}

void UUIClassSelection::SelectClass(int32 Index)
{
	ATitleGameState* State = Cast<ATitleGameState>(GetWorld()->GetGameState());
	State->NewClassID = FString(TEXT("1001"));
}
