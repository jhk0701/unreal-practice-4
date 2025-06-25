// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWMerchantUI.h"

#include "TDRPGEnum.h"
#include "Data/MerchantDataRow.h"

#include <Components/Button.h>


void UTDRPGUWMerchantUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUserWidget::Close);
}

void UTDRPGUWMerchantUI::SetMerchant(FMerchantDataRow* InMerchantData)
{
	// InMerchantData->ProductID
	// 받은 데이터로 UI 생성

}
