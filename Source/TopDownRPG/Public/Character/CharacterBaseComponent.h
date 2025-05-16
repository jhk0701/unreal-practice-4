// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UCharacterBaseComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OwnerComp)
	TObjectPtr<class ATDRPGPlayer> me;

public:	
	UCharacterBaseComponent();

	virtual void InitializeComponent() override;
		
};
