// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWPlayerUI.h"

#include "UI/TDRPGUWInventory.h"
#include "UI/TDRPGUWEquipment.h"

#include "TopDownRPG/TopDownRPG.h"


void UTDRPGUWPlayerUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PRINT_LOG(TEXT("Init Player UI"));

	if (Inventory)
		Inventory->Close();
	else
		PRINT_LOG(TEXT("Inventory is null"));

	if (Equipment)
		Equipment->Close();
	else
		PRINT_LOG(TEXT("Equipment is null"));
}
