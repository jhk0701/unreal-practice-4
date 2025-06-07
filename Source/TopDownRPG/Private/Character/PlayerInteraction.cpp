// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerInteraction.h"

#include "Core/TDRPGPlayerController.h"
#include "Character/TDRPGPlayer.h"

#include <EnhancedInputComponent.h>
#include <Components/SphereComponent.h>

#include "TopDownRPG/TopDownRPG.h"


UPlayerInteraction::UPlayerInteraction() : QuickSlotNum(0), QuickSlotMaxSize(4)
{
	QuickSlot.Init(nullptr, QuickSlotMaxSize);
}

void UPlayerInteraction::InitializeComponent()
{
	Super::InitializeComponent();
}

void UPlayerInteraction::SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController)
{
	Super::SetupInputBinding(PlayerInputComponent, InController);

	PlayerInputComponent->BindAction(InController->InteractAction,	ETriggerEvent::Started, this, &UPlayerInteraction::TriggerInteract);

	PlayerInputComponent->BindAction(InController->QuickSlotAction, ETriggerEvent::Triggered, this, &UPlayerInteraction::TriggerQuickSlot);
	PlayerInputComponent->BindAction(InController->QuickSlotAction, ETriggerEvent::Completed, this, &UPlayerInteraction::ReleaseQuickSlot);
}

void UPlayerInteraction::TriggerInteract(const FInputActionValue& Value)
{
	uint8 Input = (uint8)Value.Get<float>();
	
	switch ((EShortCutType)Input)
	{
	case EShortCutType::Interaction:
		InputInteract();
		break;
	case EShortCutType::Inventory:
		InputInventory();
		break;
	}
}

void UPlayerInteraction::InputInteract()
{
	TArray<AActor*> Overlapped;
	Player->InteractCollider->GetOverlappingActors(Overlapped, AActor::StaticClass());

	// 없으면 실행 중지
	if (Overlapped.Num() < 1)
		return;

	for (auto Iter = Overlapped.CreateConstIterator(); Iter; ++Iter)
	{
		// 첫번째 객체만 실행
		if ((*Iter)->Implements<UInteractable>())
		{
			IInteractable* Interactable = Cast<IInteractable>(*Iter);
			Interactable->Interact();
			return;
		}
	}
}

void UPlayerInteraction::InputInventory()
{
	// UI 열기
	// 이미 열려있으면 닫기


}


void UPlayerInteraction::TriggerQuickSlot(const FInputActionValue& Value)
{
	QuickSlotNum = (uint8)Value.Get<float>() - 1;
}

void UPlayerInteraction::ReleaseQuickSlot(const FInputActionValue& Value)
{
	UseQuickSlot(QuickSlotNum);
}

void UPlayerInteraction::UseQuickSlot(uint8 Idx)
{
	if (QuickSlotMaxSize <= Idx || !QuickSlot[Idx])
		return;

	QuickSlot[Idx]->InvokeSlot(Player);
}

