// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyFactory.generated.h"

UCLASS()
class TOPDOWNRPG_API AEnemyFactory : public AActor
{
	GENERATED_BODY()
	

protected:
	FTimerHandle spawnTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	TSubclassOf<class ATDRPGEnemy> enemyFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn|Setting")
	float minTime = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn|Setting")
	float maxTime = 10.f;

public:	
	AEnemyFactory();
	virtual void BeginPlay() override;

	UFUNCTION()
	void Spawn();

};