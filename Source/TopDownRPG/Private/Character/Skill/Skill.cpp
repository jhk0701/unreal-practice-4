// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Skill.h"
#include "Character/Skill/SkillEffectBase.h"
#include "Character/Input/InputProcessor.h"

#include "TDRPGEnum.h"
#include "Core/ResourceLoadManager.h"
#include "Data/SkillDataRow.h"
#include "Data/SkillConfig.h"

#include "Character/TDRPGPlayer.h"
#include "Character/PlayerAnim.h"

#include "TopDownRPG/TopDownRPG.h"


#pragma region Skill Base

void USkill::Initialize(FSkillDataRow& InData, USkillConfig* InConfig, AActor* InOwner)
{
	Owner = InOwner;

	UResourceLoadManager* Loader = Owner->GetWorld()->GetGameInstance()->GetSubsystem<UResourceLoadManager>();

	// 스킬 구성
	// 1. 스킬 모션 추가
	Motion = InConfig->Motion;
	Loader->Load(Motion, FOnResourceLoaded());

	// 2. 효과 구성
	Effect = InConfig->Effect;
	Loader->Load(
		Effect, 
		FOnResourceLoaded::CreateLambda(
			[this](UObject* Loaded)
			{
				if (ASkillEffectBase* LoadedEffect = Cast<ASkillEffectBase>(Loaded))
					EffectInstance = Owner->GetWorld()->SpawnActor<ASkillEffectBase>(LoadedEffect->StaticClass());
			}
		)
	);
}

#pragma endregion


#pragma region Active Skill

void UActiveSkill::Initialize(FSkillDataRow& InData, USkillConfig* InConfig, AActor* InOwner)
{
	Super::Initialize(InData, InConfig, InOwner);

	// 입력 처리 설정
	Input = FInputProcessorFactory::GetInstance(InData.InputType, InOwner->GetWorld());
	Input->OnInputProcessed.BindUObject(this, &UActiveSkill::OnInputProcessed);
}

void UActiveSkill::InvokeSkill()
{
	Input->Process();
}

void UActiveSkill::OnInputProcessed(const FSkillInputContext& InContext)
{
	if (InContext.bProcessIsCompleted)
		Activate(InContext);
}

/// 액티브 스킬 발동
void UActiveSkill::Activate(const FSkillInputContext& InContext)
{
	Super::Activate(InContext);

	if (ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(Owner))
	{
		// 애니메이션 실행
		Player->AnimInst->PlayAttack(Motion.Get(), InContext.Count);
	}

	if (EffectInstance)
	{
		// 이펙트 호출
		EffectInstance->Activate(Owner->GetActorLocation(), Owner->GetActorForwardVector());
	}
}

#pragma endregion


#pragma region Passive Skill

/// 패시브 발동
// 이벤트 기반으로 발동할 것
void UPassiveSkill::Activate(const FSkillInputContext& InContext)
{
	Super::Activate(InContext);
}

#pragma endregion