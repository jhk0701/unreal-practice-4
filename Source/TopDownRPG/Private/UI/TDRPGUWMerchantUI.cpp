// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWMerchantUI.h"

#include <Components/Button.h>


void UTDRPGUWMerchantUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUserWidget::Close);
}

void UTDRPGUWMerchantUI::BindData()
{
}
