// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInputComponent.generated.h"

class ATDRPGPlayer;
class ATDRPGPlayerController;
struct FInputActionValue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UPlayerInputComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OwnerComp)
	TObjectPtr<ATDRPGPlayerController> controller;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OwnerComp)
	TObjectPtr<ATDRPGPlayer> player;

public:	
	UPlayerInputComponent();
	virtual void InitializeComponent() override;
	virtual void SetupInputBinding(class UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController) {};
		
};
