// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/InventorySaveData.h"
#include "TDRPGConst.h"

FInventorySaveData::FInventorySaveData() 
	: ItemID(FTDRPGConst::EMPTY_ITEM_ID),
	ItemType(-1), 
	Quantity(0) 
{
}
