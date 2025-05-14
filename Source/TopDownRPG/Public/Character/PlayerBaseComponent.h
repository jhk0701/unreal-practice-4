// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerBaseComponent.generated.h"


class ATDRPGPlayer;
class ATDRPGPlayerController;
struct FInputActionValue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UPlayerBaseComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OwnerComp)
	TObjectPtr<ATDRPGPlayer> me;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OwnerComp)
	TObjectPtr<ATDRPGPlayerController> controller;

public:	
	UPlayerBaseComponent();
	virtual void InitializeComponent() override;
	virtual void SetupInputBinding(class UEnhancedInputComponent* PlayerInputComponent, class ATDRPGPlayerController* InController) {};
		
};
