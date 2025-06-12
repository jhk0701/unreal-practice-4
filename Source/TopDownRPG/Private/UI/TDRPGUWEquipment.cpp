// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWEquipment.h"

#include <Components/Button.h>

void UTDRPGUWEquipment::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CloseButton->OnClicked.AddUniqueDynamic(this, &UTDRPGUserWidget::Close);
}
