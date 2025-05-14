// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerBaseComponent.h"
#include "Character/TDRPGPlayer.h"

// Sets default values for this component's properties
UPlayerBaseComponent::UPlayerBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UPlayerBaseComponent::InitializeComponent()
{
	Super::InitializeComponent();

	me = Cast<ATDRPGPlayer>(GetOwner());

	me->OnInputBindDelegate.AddUObject(this, &UPlayerBaseComponent::SetupInputBinding);
}
