// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerInteraction.h"

#include "Core/TDRPGPlayerController.h"
#include "Character/TDRPGPlayer.h"

#include <EnhancedInputComponent.h>
#include <Components/SphereComponent.h>

#include "TopDownRPG/TopDownRPG.h"

#include "Core/GameDataManager.h"
#include "Item/ConsumeItem.h"
#include "Data/ConsumeDataRow.h"


UPlayerInteraction::UPlayerInteraction() : QuickSlotNum(0)
{
	QuickSlot.Init(nullptr, QuickSlotMaxSize);
}

void UPlayerInteraction::InitializeComponent()
{
	Super::InitializeComponent();

	// 테스트용 퀵슬롯 기능 추가
	FName TempID = TEXT("0000");
	UGameDataManager* GameData = GetWorld()->GetGameInstance()->GetSubsystem<UGameDataManager>();
	FConsumeDataRow* ItemData = GameData->GetRow<FConsumeDataRow>(ETableType::Consume, TempID);
	
	UConsumeItem* TestConsume = NewObject<UConsumeItem>();
	TestConsume->Initialize(*ItemData, TempID);
	uint32 Rest = 0;
	TestConsume->TryAddItem(10, Rest);

	QuickSlot[0] = TestConsume;
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

