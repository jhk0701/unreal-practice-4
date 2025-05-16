// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyMove.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UEnemyMove : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float ToleranceToTarget = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float Speed = 1000.0f;

public:	
	UEnemyMove();
	void MoveTo(const FVector& Direction);
};
