// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerInteraction.h"

#include "CommonConst.h"
#include "Core/TDRPGPlayerController.h"
#include "Character/TDRPGPlayer.h"

#include <EnhancedInputComponent.h>
#include <Components/SphereComponent.h>

#include "TopDownRPG/TopDownRPG.h"


UPlayerInteraction::UPlayerInteraction() : QuickSlotNum(0)
{
}

void UPlayerInteraction::SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController)
{
	Super::SetupInputBinding(PlayerInputComponent, InController);

	PlayerInputComponent->BindAction(InController->InteractAction,	ETriggerEvent::Started, this, &UPlayerInteraction::InvokeInteract);

	PlayerInputComponent->BindAction(InController->QuickSlotAction, ETriggerEvent::Triggered, this, &UPlayerInteraction::TriggerQuickSlot);
	PlayerInputComponent->BindAction(InController->QuickSlotAction, ETriggerEvent::Completed, this, &UPlayerInteraction::ReleaseQuickSlot);
}

void UPlayerInteraction::InvokeInteract(const FInputActionValue& Value)
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

void UPlayerInteraction::TriggerQuickSlot(const FInputActionValue& Value)
{
	QuickSlotNum = (uint8)Value.Get<float>();
}

void UPlayerInteraction::ReleaseQuickSlot(const FInputActionValue& Value)
{
	// PRINT_LOG(TEXT("Quick Slot : %u"), QuickSlotNum);
	// TODO : 퀵슬롯 연동
}

