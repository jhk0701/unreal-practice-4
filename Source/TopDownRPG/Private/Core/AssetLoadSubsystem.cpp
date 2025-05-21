// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AssetLoadSubsystem.h"


template<class T>
T* UAssetLoadSubsystem::Load(const FString& Path)
{
	return LoadObject<T>(NULL, Path, NULL, LOAD_None, NULL);
}