// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/CharacterBaseComponent.h"
#include "Character/TDRPGPlayer.h"

// Sets default values for this component's properties
UCharacterBaseComponent::UCharacterBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UCharacterBaseComponent::InitializeComponent()
{
	Super::InitializeComponent();

	me = Cast<ATDRPGPlayer>(GetOwner());
}
