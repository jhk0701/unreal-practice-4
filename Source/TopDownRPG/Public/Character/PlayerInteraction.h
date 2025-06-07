// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlayerInputComponent.h"
#include "Inherit/QuickSlotHandler.h"
#include "PlayerInteraction.generated.h"



/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UPlayerInteraction : public UPlayerInputComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "QuickSlot")
	uint8 QuickSlotMaxSize = 4;
	UPROPERTY(VisibleAnywhere, Category = "QuickSlot")
	uint8 QuickSlotNum = 0;

	// 퀵슬롯 기능
	// 우선 1~4번에 소비 아이템 할당 
	// 인터페이스를 상속한 객체 담기
	// 인터페이스를 담기 위해 TScriptInterface 사용
	// 이 기능은 나중에 생각해볼것 만약 소비 아이템 외의 바인딩이 필요하다면?
	// 슬롯 핸들러 : 아이템 외에도 여럿을 담을 수 있는 객체 or 인터페이스
	UPROPERTY(VisibleAnywhere, Category = "QuickSlot")
	TArray<TScriptInterface<IQuickSlotHandler>> QuickSlot;


public:
	UPlayerInteraction();
	virtual void SetupInputBinding(class UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController) override;
	
	void InputInteract(const FInputActionValue& Value);
	void InputInventory(const FInputActionValue& Value);
	
	// 퀵슬롯 입력
	void TriggerQuickSlot(const FInputActionValue& Value);
	void ReleaseQuickSlot(const FInputActionValue& Value);
	void UseQuickSlot(uint8 Idx);
};
