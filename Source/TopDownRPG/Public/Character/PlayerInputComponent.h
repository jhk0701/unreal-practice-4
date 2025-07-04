// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Input/InputHandler.h"
#include "PlayerInputComponent.generated.h"

class UEnhancedInputComponent;

class ATDRPGPlayer;
class ATDRPGPlayerController;
struct FInputActionValue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UPlayerInputComponent : public UActorComponent, public IInputHandler
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OwnerComp)
	TObjectPtr<ATDRPGPlayer> Player;

public:	
	UPlayerInputComponent();
	virtual void InitializeComponent() override;
	virtual void SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController) override {};
};
