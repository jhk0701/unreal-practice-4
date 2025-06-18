
// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TDRPGUWEquipmentMenu.h"

#include <Components/TextBlock.h>

#include "Core/PlayerManager.h"
#include "Item/EquipmentItem.h"


void UTDRPGUWEquipmentMenu::InvokeFunc()
{
	if (UEquipmentItem* Equipment = Cast<UEquipmentItem>(SelectedItem)) 
	{
		UPlayerManager* PlayerManager = GetGameInstance()->GetSubsystem<UPlayerManager>();
		Equipment->Unequip(PlayerManager);
	}

	Super::InvokeFunc();
}
