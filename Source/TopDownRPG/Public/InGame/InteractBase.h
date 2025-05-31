// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inherit/Interactable.h"
#include "InteractBase.generated.h"

UCLASS()
class TOPDOWNRPG_API AInteractBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction)
	TObjectPtr<class UBoxComponent> InteractCollider;

	// TODO : 접근 시 활성화되는 인터랙션 UI 추가

public:	
	AInteractBase();
	virtual void BeginPlay() override;
	virtual void Interact() override {};

	UFUNCTION()
	virtual void OnBeginOverlapped(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	virtual void OnEndOverlapped(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
};
