// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/TDRPGUserWidget.h"
#include <Templates/EnableIf.h>
#include <Engine/AssetManager.h>
#include <Engine/StreamableManager.h>
#include "TopDownRPG/TopDownRPG.h"
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
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

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
		
		FStreamableManager& stream = UAssetManager::GetStreamableManager();
		FSoftClassPath UIPath(FString::Format(TEXT("/Game/4-UI/WBP_{0}.WBP_{0}_C"), { name }));

		stream.RequestAsyncLoad(
			UIPath, 
			FStreamableDelegate::CreateLambda(
				[this, UIPath, name, OnCompleted]()
				{
					UClass* WidgetClass = Cast<UClass>(UIPath.ResolveObject());
					if (WidgetClass)
					{
						UTDRPGUserWidget* widget = CreateWidget<UTDRPGUserWidget>(this->GetWorld(), WidgetClass);

						this->UIMap.Add(name, widget);

						OnCompleted.ExecuteIfBound(widget);
					}
				}));
	};
};
