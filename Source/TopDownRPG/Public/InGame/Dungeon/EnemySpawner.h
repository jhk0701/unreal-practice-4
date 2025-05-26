// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemySpawner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UEnemySpawner : public UActorComponent
{
	GENERATED_BODY()

public:


public:	
	UEnemySpawner();
	virtual void BeginPlay() override;
		
};
