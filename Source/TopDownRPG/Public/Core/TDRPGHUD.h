// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <Templates/EnableIf.h>
#include <Engine/AssetManager.h>
#include "TDRPGHUD.generated.h"

enum class EUILayer :uint8;
class UUIConfig;
class UTDRPGUserWidget;
class UTDRPGUWCanvas;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ATDRPGHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATDRPGHUD();

	template<typename T>
	inline TEnableIf<TIsDerivedFrom<T, UTDRPGUserWidget>::Value, T*>::type
	GetUI()
	{
		FString Name = FString::Printf(TEXT("WBP_%s_C"), *GetNameFromType<T>().ToString());

		if (UIMap.Contains(Name))
			return Cast<T>(UIMap[Name]);

		return nullptr;
	}
protected:
	UPROPERTY()
	TMap<FString, UTDRPGUserWidget*> UIMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI|Canvas")
	TSubclassOf<UTDRPGUWCanvas> CanvasFactory;

	UPROPERTY()
	TMap<EUILayer, UTDRPGUWCanvas*> Layer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	TArray<TObjectPtr<UUIConfig>> Configs;


	virtual void PostInitializeComponents() override;
	void InitHUD();

	inline void ClearUIMap() { UIMap.Empty(); };

	void InitCanvas();
	UTDRPGUWCanvas* CreateCanvas();

	void InitUIConfig(UUIConfig* InConfig);


	template<typename T>
	inline TEnableIf<TIsDerivedFrom<T, UTDRPGUserWidget>::Value, FName>::type
	GetNameFromType()
	{
		UClass* Type = T::StaticClass();
		check(Type); // 방어용

		return Type->GetFName();
	}
};
