// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataModel.h"

void UDataModel::Initialize(FString& InID, UGameDataManager* InDB)
{
	ID = InID;
	DB = InDB;
}
