// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Skill.h"
#include "Character/Input/InputProcessor.h"

#include "TDRPGConst.h"
#include "TDRPGEnum.h"
#include "Core/GameDataManager.h"
#include "Core/ResourceLoadManager.h"
#include "Data/SkillDataRow.h"
#include "Data/SkillConfig.h"

#include "Character/TDRPGPlayer.h"
#include "Character/TDRPGEnemy.h"
#include "Character/CharacterAnimBase.h"
#include "Character/CharacterData.h"
#include "Character/PlayerAction.h"

#include "TopDownRPG/TopDownRPG.h"
#include <DrawDebugHelpers.h>


#pragma region Skill Base

void USkill::Initialize(const FString& InID, UGameDataManager* InDB, AActor* InOwner)
{
	Owner = InOwner;
	Super::Initialize(InID, InDB);

	UResourceLoadManager* Loader = Owner->GetWorld()->GetGameInstance()->GetSubsystem<UResourceLoadManager>();

	// Skill 데이터 호출
	FSkillDataRow* SkillData = DB->GetRow<FSkillDataRow>(ETableType::Skill, ID);
	check(SkillData);
	Data = *SkillData;

	// Skill Config 로드
	FPrimaryAssetId ConfigID(FTDRPGConst::CONFIG_SKILL, *ID);
	UPrimaryDataAsset* DataAsset = DB->LoadPrimaryAssetData(ConfigID);
	check(DataAsset);

	USkillConfig* Config = Cast<USkillConfig>(DataAsset);

	// 스킬 구성
	// 1. 스킬 모션 추가
	Motion = Config->Motion;
	Loader->Load(Motion.ToSoftObjectPath(), FOnResourceLoaded());

	// 2. 효과 구성
	Effect = Config->Effect;
	Loader->Load(Effect.ToSoftObjectPath(), FOnResourceLoaded());
}


void USkill::Activate(const FSkillInputContext& InContext)
{
	// 스킬 이벤트
	OnSkillStarted.Broadcast();
}

#pragma endregion


#pragma region Active Skill

void UActiveSkill::Initialize(const FString& InID, UGameDataManager* InDB, AActor* InOwner)
{
	Super::Initialize(InID, InDB, InOwner);

	// 입력 처리 설정
	Input = FInputProcessorFactory::GetInstance(Data.InputType, InOwner->GetWorld());
	Input->OnInputProcessed.BindUObject(this, &UActiveSkill::OnInputProcessed);
}


/// 액티브 스킬 발동
void UActiveSkill::Activate(const FSkillInputContext& InContext)
{
	Super::Activate(InContext);

	UCharacterAnimBase* AnimInst;
	if (ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(Owner))
		AnimInst = Player->GetAnim();
	else if (ATDRPGEnemy* Enemy = Cast<ATDRPGEnemy>(Owner))
		AnimInst = Enemy->GetAnim();
	else
		return;

	AnimInst->OnHitStarted.Clear();
	// AnimInst->OnHitEnded.Clear();

	// 이펙트 호출 -> 애니메이션 이벤트 노티파이에서 사용
	AnimInst->OnHitStarted.AddUObject(this, &UActiveSkill::ShowEffect);
	AnimInst->OnHitStarted.AddUObject(this, &UActiveSkill::InvokeSweep);

	// 애니메이션 실행
	AnimInst->PlayAttack(Motion.Get(), InContext.Count);
}

void UActiveSkill::InvokeSkill()
{
	// 스킬 자원 소모
	if(ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(Owner))
	{
		if (!Player->ActionComp->TryUseResource(Data.Requirement))
		{
			PRINT_LOG(TEXT("Resource is not enough."));
			return;
		}
	}

	Input->Process();
}

void UActiveSkill::OnInputProcessed(const FSkillInputContext& InContext)
{
	if (InContext.bProcessIsCompleted)
		Activate(InContext);
}

void UActiveSkill::ShowEffect()
{
	// TODO : 이펙트 호출
}

void UActiveSkill::InvokeSweep()
{
	if (!Owner)
		return;

	// 충돌 검사
	TArray<FHitResult> Hits;
	FVector Start;
	FVector End;

	FCollisionQueryParams Param;
	Param.AddIgnoredActor(Owner);

	FCollisionShape Shape;

	switch (Data.Direction)
	{
	case ESkillDirection::Forward:
		Start = Owner->GetActorLocation();
		End = Start + Owner->GetActorForwardVector() * Data.Range;
		Shape = FCollisionShape::MakeSphere(Data.Size);
		break;

	case ESkillDirection::AllDirection:
		Start = Owner->GetActorLocation();
		End = Start;
		Shape = FCollisionShape::MakeSphere(Data.Range);
		break;
	}

	DrawDebugLine(Owner->GetWorld(), Start, End, FColor::Red, false, 1.0f);
	DrawDebugSphere(Owner->GetWorld(), End, Data.Size, 12, FColor::Red, false , 1.0f, 0, 1.0f);

	if (!Owner->GetWorld()->
		SweepMultiByChannel(Hits, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, Shape, Param)) 
		return;

	AdjustDamage(Hits);
}

void UActiveSkill::AdjustDamage(const TArray<FHitResult>& InHits)
{
	for (auto& Hit : InHits)
	{
		AActor* HittedActor = Hit.GetActor();
		int32 BaseDamage = FMath::RandRange(Data.MinDamage, Data.MaxDamage);

		// TODO : 리팩토링 필요
		if (Owner->Tags.Contains(FTDRPGConst::TAG_PLAYER))
		{
			if (ATDRPGEnemy* Enemy = Cast<ATDRPGEnemy>(HittedActor))
			{
				// 데미지 적용
				ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(Owner);
				uint32 Damage = Player->DataComp->GetAttackPower(BaseDamage);

				Enemy->TakeDamage(Damage);
			}
		}
		else if (Owner->Tags.Contains(FTDRPGConst::TAG_ENEMY))
		{
			if (ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(HittedActor))
			{
				ATDRPGEnemy* Enemy = Cast<ATDRPGEnemy>(Owner);
				uint32 Damage = Enemy->DataComp->GetAttackPower(BaseDamage);

				Player->TakeDamage(Damage);
			}
		}

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