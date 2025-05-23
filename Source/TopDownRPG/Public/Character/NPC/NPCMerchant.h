// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NPC/TDRPGNPCBase.h"
#include "Inherit/Interactable.h"
#include "NPCMerchant.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ANPCMerchant : public ATDRPGNPCBase, public IInteractable
{
	GENERATED_BODY()

protected:
	// 접근 시 활성화되는 인터랙션 UI
	
	// 접근 감지용 콜라이더
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Merchant")
	TObjectPtr<class USphereComponent> DetectArea;

public:
	ANPCMerchant();
	virtual void BeginPlay() override;		// TODO : 취급 데이터 받아오기
	virtual void Interact() override;

	UFUNCTION()
	void OnBeginOverlapped(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnEndOverlapped(
		UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex
	);
};
