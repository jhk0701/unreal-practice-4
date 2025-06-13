// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/TDRPGHUD.h"
#include "TitleHUD.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ATitleHUD : public ATDRPGHUD
{
	GENERATED_BODY()

public:
	void Initialize() override;
};
