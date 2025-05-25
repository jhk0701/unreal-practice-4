// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/TDRPGUserWidget.h"
#include <Templates/EnableIf.h>
#include <Engine/AssetManager.h>
#include <Engine/StreamableManager.h>
#include "CommonConst.h"
#include "UISubsystem.generated.h"


DECLARE_DELEGATE_OneParam(FOnLoadCompleted, UTDRPGUserWidget*);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TMap<FString, UTDRPGUserWidget*> UIMap;

public:
	template<typename T>
	inline typename TEnableIf<TIsDerivedFrom<T, UTDRPGUserWidget>::Value, void>::type
	CreateUI(FOnLoadCompleted& OnCompleted)
	{
		UClass* type = T::StaticClass();
		check(type);
		FString name = type->GetFName().ToString();

		FStreamableManager& stream = UAssetManager::GetStreamableManager();
		FSoftClassPath path(FString::Format(*CommonConst::PATH_FORMAT_UI, { name }));

		stream.RequestAsyncLoad(
			path,
			FStreamableDelegate::CreateLambda(
				[this, path, name, OnCompleted]()
				{
					UClass* WidgetClass = Cast<UClass>(path.ResolveObject());
					if (WidgetClass)
					{
						UTDRPGUserWidget* widget = CreateWidget<UTDRPGUserWidget>(this->GetWorld(), WidgetClass);

						this->UIMap.Add(name, widget);

						OnCompleted.ExecuteIfBound(widget);
					}
				}));
	}

	template<typename T>
	inline typename TEnableIf<TIsDerivedFrom<T, UTDRPGUserWidget>::Value, void>::type
	GetUI(FOnLoadCompleted&& OnCompleted)
	{
		UClass* type = T::StaticClass();
		check(type);
		FString name = type->GetFName().ToString();

		if (UIMap.Contains(name) && IsValid(UIMap[name]))
		{
			OnCompleted.ExecuteIfBound(UIMap[name]);
			return;
		}
		else if(UIMap.Contains(name))
			UIMap.Remove(name);

		CreateUI<T>(OnCompleted);
	};
};
