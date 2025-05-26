// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle	UMETA(DisplayName = "Idle"),
	Move	UMETA(DisplayName = "Move"),
	Attack	UMETA(DisplayName = "Attack"),
	Dead	UMETA(DisplayName = "Dead")
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	TObjectPtr<class UBaseState> curState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	TMap<EEnemyState, TObjectPtr<UBaseState>> stateMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Owner)
	TObjectPtr<class ATDRPGEnemy> owner;

public:	
	UEnemyFSM();
	
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Transition(EEnemyState type);
	TObjectPtr<ATDRPGEnemy> GetOwnerEnemy();
};
