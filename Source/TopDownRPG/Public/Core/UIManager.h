// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/TDRPGUserWidget.h"
#include "CommonConst.h"
#include <Templates/EnableIf.h>
#include <Engine/AssetManager.h>
#include <Engine/StreamableManager.h>
#include "UIManager.generated.h"

class UUIConfig;
class ATDRPGHUD;

DECLARE_DELEGATE_OneParam(FOnLoadCompleted, UTDRPGUserWidget*);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TMap<FString, UTDRPGUserWidget*> UIMap;

	UPROPERTY()
	TObjectPtr<ATDRPGHUD> CurrentHUD;

public:
	void SetHUD(ATDRPGHUD* InHUD);
	inline ATDRPGHUD* GetHUD() { return CurrentHUD; };

	inline void ClearUIMap() { UIMap.Empty(); };

	void InitUIConfig(UUIConfig* InConfig);

	template<typename T>
	inline TEnableIf<TIsDerivedFrom<T, UTDRPGUserWidget>::Value, T*>::type
	GetUI() 
	{
		FString Name = FString::Printf(TEXT("WBP_%s_C"), *GetNameFromType<T>().ToString());

		if (UIMap.Contains(Name))
			return Cast<T>(UIMap[Name]);

		return nullptr;
	}

	template<typename T>
	inline TEnableIf<TIsDerivedFrom<T, UTDRPGUserWidget>::Value, FName>::type
	GetNameFromType()
	{
		UClass* Type = T::StaticClass();
		check(Type); // 방어용

		return Type->GetFName();
	}

	// 템플릿으로 작성
	// 상속해서 만든 UserWidget에서 파생한 UI만 호출할 수 있도록 사용
	/*
		TEnableIf<condition, ret>::type
			* 조건에 맞으면 ret 반환형 사용
			* 그렇지 않으면 생성 취소
		 
		TIsDerivedFrom<baseType, parentType>::Value
			* baseType이 parentType의 자식클래스라면 true
	*/
	template<typename T>
	inline typename TEnableIf<TIsDerivedFrom<T, UTDRPGUserWidget>::Value, void>::type
	CreateUI(FOnLoadCompleted& OnCompleted)
	{
		FString Name = GetNameFromType<T>().ToString();

		FStreamableManager& Stream = UAssetManager::GetStreamableManager();
		FSoftClassPath Path(FString::Format(*CommonConst::PATH_FORMAT_UI, { Name }));

		Stream.RequestAsyncLoad(
			Path,
			FStreamableDelegate::CreateLambda(
				[this, Path, Name, OnCompleted]()
				{
					UClass* WidgetClass = Cast<UClass>(Path.ResolveObject());
					if (WidgetClass)
					{
						UTDRPGUserWidget* Widget = CreateWidget<UTDRPGUserWidget>(this->GetWorld(), WidgetClass);

						this->UIMap.Add(Name, Widget);
						OnCompleted.ExecuteIfBound(Widget);
					}
				}));
	}

	template<typename T>
	inline typename TEnableIf<TIsDerivedFrom<T, UTDRPGUserWidget>::Value, void>::type
	GetUI(FOnLoadCompleted&& OnCompleted)
	{
		FString Name = GetNameFromType<T>().ToString();

		if (UIMap.Contains(Name) && IsValid(UIMap[Name]))
		{
			OnCompleted.ExecuteIfBound(UIMap[Name]);
			return;
		}
		
		if (UIMap.Contains(Name))
			UIMap.Remove(Name);

		CreateUI<T>(OnCompleted);
	};

};
