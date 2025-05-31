// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InGame/InteractBase.h"
#include "TDRPGNPCBase.generated.h"

UCLASS()
class TOPDOWNRPG_API ATDRPGNPCBase : public AInteractBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Comp")
	TObjectPtr<class UCapsuleComponent> Collider;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Comp")
	TObjectPtr<USkeletalMeshComponent> SkinnedMesh;

public:	
	ATDRPGNPCBase();
};
