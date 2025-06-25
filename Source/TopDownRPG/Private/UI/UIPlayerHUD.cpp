// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIPlayerHUD.h"

#include "UI/UIInventory.h"
#include "UI/UIEquipment.h"
#include "UI/UIStatusWindow.h"

#include "TopDownRPG/TopDownRPG.h"


void UUIPlayerHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Inventory)
		Inventory->Close();

	if (Equipment)
		Equipment->Close();

	if (StatusWindow)
		StatusWindow->Close();
}
