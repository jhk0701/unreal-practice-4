// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerInteraction.h"
#include "Character/TDRPGPlayer.h"
#include "Core/TDRPGPlayerController.h"
#include "CommonConst.h"
#include <EnhancedInputComponent.h>
#include <Components/SphereComponent.h>


UPlayerInteraction::UPlayerInteraction()
{
}

void UPlayerInteraction::SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController)
{
	Super::SetupInputBinding(PlayerInputComponent, InController);

	PlayerInputComponent->BindAction(InController->InteractAction, ETriggerEvent::Started, this, &UPlayerInteraction::InvokeInteract);
}

void UPlayerInteraction::InvokeInteract(const FInputActionValue& Value)
{
	TArray<AActor*> Overlapped;
	player->interactCollider->GetOverlappingActors(Overlapped, AActor::StaticClass());

	// 없으면 실행 중지
	if (Overlapped.Num() < 1)
		return;
	
	for (auto iter = Overlapped.CreateConstIterator(); iter; ++iter)
	{
		// 첫번째 객체만 실행
		if ((*iter)->Implements<UInteractable>()) 
		{
			IInteractable* interactable = Cast<IInteractable>(*iter);
			interactable->Interact();
			return;
		}
	}
}
