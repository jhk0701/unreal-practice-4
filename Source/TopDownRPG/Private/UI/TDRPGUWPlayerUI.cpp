// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWPlayerUI.h"

#include "UI/TDRPGUWInventory.h"
#include "UI/TDRPGUWEquipment.h"

#include "TopDownRPG/TopDownRPG.h"


void UTDRPGUWPlayerUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Inventory)
		Inventory->Close();

	if (Equipment)
		Equipment->Close();
}
