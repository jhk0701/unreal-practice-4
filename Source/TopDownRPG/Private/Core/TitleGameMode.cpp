// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TitleGameMode.h"
#include "Core/TitleHUD.h"

ATitleGameMode::ATitleGameMode()
{
	HUDClass = ATitleHUD::StaticClass();
}
