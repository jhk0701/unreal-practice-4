// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Inherit/QuickSlotHandler.h"
#include "QuickSlot.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuickSlotDelegate, uint8);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UQuickSlot : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "QuickSlot")
	uint8 QuickSlotMaxSize = 4;

	/*
		우선 1~4번에 소비 아이템 할당 
		인터페이스를 상속한 객체 담기
		인터페이스를 담기 위해 TScriptInterface 사용
		이 기능은 나중에 생각해볼것 만약 소비 아이템 외의 바인딩이 필요하다면?
		슬롯 핸들러 : 아이템 외에도 여럿을 담을 수 있는 객체 or 인터페이스
	*/
	UPROPERTY(VisibleAnywhere, Category = "QuickSlot")
	TArray<TScriptInterface<IQuickSlotHandler>> Slots;

	FOnQuickSlotDelegate OnSlotRegistered;

public:
	UQuickSlot();

	bool Register(IQuickSlotHandler* InSlot);
	void Use(uint8 Idx, AActor* Target);


};
