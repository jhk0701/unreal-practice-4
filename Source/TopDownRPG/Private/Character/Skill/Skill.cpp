// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Skill.h"
#include "Character/Skill/SkillEffectBase.h"

#include "TDRPGEnum.h"
#include "Data/SkillDataRow.h"
#include "Character/Input/InputProcessor.h"

#include "Core/ResourceLoadManager.h"

#include "TopDownRPG/TopDownRPG.h"


void USkill::Initialize(FSkillDataRow& InData, AActor* InOwner)
{
	Owner = InOwner;

	UResourceLoadManager* Loader = Owner->GetWorld()->GetGameInstance()->GetSubsystem<UResourceLoadManager>();
	// 스킬 구성
	// 1. 스킬 모션 추가
	Motion = TSoftObjectPtr<UAnimMontage>(InData.MotionPath);
	Loader->Load(Motion);

	// 2. TODO : 효과 구성
}

void USkill::Activate()
{
	PRINT_LOG(TEXT("Skill Activate"));
}


void UActiveSkill::Initialize(FSkillDataRow& InData, AActor* InOwner)
{
	Super::Initialize(InData, InOwner);

	// 입력 처리 설정
	Input = FInputProcessorFactory::GetInstance(InData.InputType, InOwner->GetWorld());
	Input->OnInputProcessed.BindUObject(this, &UActiveSkill::OnInputProcessed);

}

void UActiveSkill::InvokeSkill()
{
	Input->Process();
}

/// <summary>
/// 액티브 스킬 발동
/// </summary>
void UActiveSkill::Activate()
{
	Super::Activate();
	
	
	/*if (Motion.IsValid())
		Motion.Get();*/
}

void UActiveSkill::OnInputProcessed(const FSkillInputContext& InContext)
{
	PRINT_LOG(TEXT("Skill Activate"));
	Activate();
}


/// <summary>
/// 패시브 발동
/// </summary>
void UPassiveSkill::Activate()
{
}
