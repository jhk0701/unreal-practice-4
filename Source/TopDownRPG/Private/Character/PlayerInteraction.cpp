// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerInteraction.h"

#include "Core/TDRPGPlayerController.h"
#include "Character/TDRPGPlayer.h"

#include "Core/PlayerManager.h"
#include "Player/QuickSlot.h"

#include "Core/UIManager.h"
#include "UI/TDRPGUWInventory.h"
#include "UI/TDRPGUWEquipment.h"

#include <EnhancedInputComponent.h>
#include <Components/SphereComponent.h>

#include "TopDownRPG/TopDownRPG.h"


UPlayerInteraction::UPlayerInteraction()
{
	QuickSlotNumInput = 0;
}

void UPlayerInteraction::SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController)
{
	Super::SetupInputBinding(PlayerInputComponent, InController);

	PlayerInputComponent->BindAction(InController->InteractAction,	ETriggerEvent::Started, this, &UPlayerInteraction::InputInteract);
	PlayerInputComponent->BindAction(InController->InventoryAction, ETriggerEvent::Started, this, &UPlayerInteraction::InputInventory);
	PlayerInputComponent->BindAction(InController->EquipmentAction, ETriggerEvent::Started, this, &UPlayerInteraction::InputEquipment);

	PlayerInputComponent->BindAction(InController->QuickSlotAction, ETriggerEvent::Triggered, this, &UPlayerInteraction::TriggerQuickSlot);
	PlayerInputComponent->BindAction(InController->QuickSlotAction, ETriggerEvent::Completed, this, &UPlayerInteraction::ReleaseQuickSlot);
}


void UPlayerInteraction::InputInteract(const FInputActionValue& Value)
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

void UPlayerInteraction::InputInventory(const FInputActionValue& Value)
{
	// UI 열기
	UUIManager* UIManager = GetWorld()->GetGameInstance()->GetSubsystem<UUIManager>();
	if (!UIManager)
		return;

	UIManager->GetUI<UTDRPGUWInventory>(
		FOnLoadCompleted::CreateLambda(
			[](UTDRPGUserWidget* Loaded) {
				if (!Loaded->IsInViewport())
					Loaded->Open();
				else
					Loaded->Close();
			})
	);
}

void UPlayerInteraction::InputEquipment(const FInputActionValue& Value)
{	
	// UI 열기
	UUIManager* UIManager = GetWorld()->GetGameInstance()->GetSubsystem<UUIManager>();
	if (!UIManager)
		return;

	UIManager->GetUI<UTDRPGUWEquipment>(
		FOnLoadCompleted::CreateLambda([](UTDRPGUserWidget* Loaded){
			if (!Loaded->IsInViewport())
				Loaded->Open();
			else
				Loaded->Close();
		})
	);
}


void UPlayerInteraction::TriggerQuickSlot(const FInputActionValue& Value)
{
	QuickSlotNumInput = (uint8)Value.Get<float>() - 1;
}

void UPlayerInteraction::ReleaseQuickSlot(const FInputActionValue& Value)
{
	UseQuickSlot(QuickSlotNumInput);
}

void UPlayerInteraction::UseQuickSlot(uint8 Idx)
{
	UPlayerManager* PlayerManager = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerManager>();
	PlayerManager->QuickSlot->Use(Idx, Player);
}

