// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Skill.h"
#include "Character/Input/InputProcessor.h"

#include "TDRPGConst.h"
#include "TDRPGEnum.h"
#include "Core/ResourceLoadManager.h"
#include "Data/SkillDataRow.h"
#include "Data/SkillConfig.h"

#include "Character/TDRPGPlayer.h"
#include "Character/TDRPGEnemy.h"
#include "Character/CharacterAnimBase.h"
#include "Character/PlayerAnim.h"
#include "Character/CharacterData.h"

#include "TopDownRPG/TopDownRPG.h"


#pragma region Skill Base

void USkill::Initialize(FSkillDataRow& InData, USkillConfig* InConfig, AActor* InOwner)
{
	Owner = InOwner;

	Range = InData.Range;
	Direction = InData.Direction;
	MinDamage = InData.MinDamage;
	MaxDamage = InData.MaxDamage;
	Requirement = InData.Requirement;
	Cooldown = InData.Cooldown;

	UResourceLoadManager* Loader = Owner->GetWorld()->GetGameInstance()->GetSubsystem<UResourceLoadManager>();

	// 스킬 구성
	// 1. 스킬 모션 추가
	Motion = InConfig->Motion;
	Loader->Load(Motion.ToSoftObjectPath(), FOnResourceLoaded());

	// 2. 효과 구성
	Effect = InConfig->Effect;
	Loader->Load(Effect.ToSoftObjectPath(), FOnResourceLoaded());
}

void USkill::Activate(const FSkillInputContext& InContext)
{
	// 스킬 이벤트
	OnSkillStarted.Broadcast();
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

/// 액티브 스킬 발동
void UActiveSkill::Activate(const FSkillInputContext& InContext)
{
	Super::Activate(InContext);

	if (ATDRPGPlayer* Player = Cast<ATDRPGPlayer>(Owner))
	{
		UPlayerAnim* AnimInst = Player->AnimInst;
		AnimInst->OnHitStarted.Clear();
		// AnimInst->OnHitEnded.Clear();

		// 이펙트 호출 -> 애니메이션 이벤트 노티파이에서 사용
		AnimInst->OnHitStarted.AddUObject(this, &UActiveSkill::ShowEffect);
		AnimInst->OnHitStarted.AddUObject(this, &UActiveSkill::InvokeSweep);

		// 애니메이션 실행
		AnimInst->PlayAttack(Motion.Get(), InContext.Count);
	}
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

	switch (Direction)
	{
	case ESkillDirection::Forward:
		Start = Owner->GetActorLocation();
		End = Start + Owner->GetActorForwardVector() * Range;
		Shape = FCollisionShape::MakeSphere(Size);
		break;
	case ESkillDirection::AllDirection:
		Start = Owner->GetActorLocation();
		End = Start;
		Shape = FCollisionShape::MakeSphere(Range);
		break;
	}

	DrawDebugLine(Owner->GetWorld(), Start, End, FColor::Red, false, 1.0f);
	DrawDebugSphere(Owner->GetWorld(), Start, Size, 32, FColor::Red, false , 1.0f);

	if (Owner->GetWorld()->
		SweepMultiByChannel(
			Hits, Start, End, FQuat::Identity, 
			ECollisionChannel::ECC_GameTraceChannel2,
			Shape, Param)) 
	{
		for(auto& Hit: Hits)
		{
			AActor* HittedActor = Hit.GetActor();
			int32 BaseDamage = FMath::RandRange(MinDamage, MaxDamage);

			if (Owner->Tags.Contains(FTDRPGConst::TAG_PLAYER))
			{
				if(ATDRPGEnemy* Enemy = Cast<ATDRPGEnemy>(HittedActor))
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
					ATDRPGEnemy* Enemy  = Cast<ATDRPGEnemy>(Owner);
					uint32 Damage = Enemy->DataComp->GetAttackPower(BaseDamage);

					Player->TakeDamage(Damage);
				}
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