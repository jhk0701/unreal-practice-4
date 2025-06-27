// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/InventorySaveData.h"
#include "CommonConst.h"

FInventorySaveData::FInventorySaveData() 
	: ItemID(CommonConst::EMPTY_ITEM_ID), 
	ItemType(-1), 
	Quantity(0) 
{
}
