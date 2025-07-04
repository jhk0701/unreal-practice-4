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
	Loader->Load(Effect, FOnResourceLoaded());
}

ASkillEffectBase* USkill::GetEffect()
{
	if (EffectPool.IsEmpty())
		return CreateEffect();
	
	ASkillEffectBase* Instance;
	EffectPool.Dequeue(Instance);

	return Instance;
}

ASkillEffectBase* USkill::CreateEffect()
{
	if (Effect.IsValid())
	{
		ASkillEffectBase* Instance = Owner->GetWorld()->SpawnActor<ASkillEffectBase>(Effect.Get());
		Instance->Initialize(Owner);
		Instance->OnSkillEnded.AddUObject(this, &USkill::ReleaseEffect);

		return Instance;
	}
	
	PRINT_LOG(TEXT("Effect is not loaded."));
	return nullptr;
}

void USkill::ReleaseEffect(AActor* InInstance)
{
	if (ASkillEffectBase* EffectInst = Cast<ASkillEffectBase>(InInstance))
		EffectPool.Enqueue(EffectInst);
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

	if (ASkillEffectBase* SkillInst = GetEffect())
	{
		// 이펙트 호출
		SkillInst->Activate();
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