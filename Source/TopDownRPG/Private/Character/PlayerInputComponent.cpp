// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/PlayerInputComponent.h"
#include "Character/TDRPGPlayer.h"

// Sets default values for this component's properties
UPlayerInputComponent::UPlayerInputComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UPlayerInputComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Player = Cast<ATDRPGPlayer>(GetOwner());
	Player->OnInputBindDelegate.AddUObject(this, &UPlayerInputComponent::SetupInputBinding);
}


