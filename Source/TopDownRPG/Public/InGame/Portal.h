// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InGame/InteractBase.h"
#include "Portal.generated.h"

UCLASS()
class TOPDOWNRPG_API APortal : public AInteractBase
{
	GENERATED_BODY()

public:	
	APortal();
	virtual void BeginPlay() override;
	virtual void Interact() override;

};
