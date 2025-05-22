// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Test.generated.h"

UCLASS()
class TOPDOWNRPG_API ATest : public AActor
{
	GENERATED_BODY()
	
public:	
	ATest();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Testing)
	TObjectPtr<UStaticMeshComponent> MainMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Testing)
	TSoftObjectPtr<class UTDRPGUWTitle> UI;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Testing)
	FSoftObjectPath UIPath;

	UStaticMesh* LoadSync();
	void LoadAsync();
};
