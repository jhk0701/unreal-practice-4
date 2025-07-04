// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerAction.h"
#include "Core/TDRPGPlayerController.h"

#include "Character/TDRPGPlayer.h"
#include "Character/TDRPGEnemy.h"
#include "Character/CharacterData.h"
#include "Character/PlayerAnim.h"

#include "TDRPGEnum.h"
#include "Character/Skill/Skill.h"

#include <EnhancedInputComponent.h>
#include <Components/SphereComponent.h>

#include "TopDownRPG/TopDownRPG.h"


UPlayerAction::UPlayerAction(){}

void UPlayerAction::InitializeComponent()
{
	Super::InitializeComponent();

	Player = Cast<ATDRPGPlayer>(GetOwner());
	Player->OnInputBindDelegate.AddUObject(this, &UPlayerAction::SetupInputBinding);
}

void UPlayerAction::SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController)
{
	PlayerInputComponent->BindAction(InController->AttackDefaultAction, ETriggerEvent::Triggered, this, &UPlayerAction::InputAttack);
	PlayerInputComponent->BindAction(InController->SkillAction, ETriggerEvent::Triggered, this, &UPlayerAction::InputSkill);
}

void UPlayerAction::InputAttack(const FInputActionValue& InputValue)
{
	if (Player->CheckPlayerIsDead())
		return;

	InvokeAttack();
}

void UPlayerAction::InvokeAttack()
{
	if (!Player->AnimInst || Player->AnimInst->IsAttackPlaying())
		return;

	Player->InvokeAttackDelegate(); // 이동 기능은 꺼질 것
	
	// 커서 방향으로 바라보도록
	FHitResult HitResult;
	Player->GetMouseToWorld(HitResult);

	FVector Dir = HitResult.ImpactPoint - Player->GetActorLocation();
	Player->SetActorRotation(Dir.ToOrientationQuat());

	// 일반 공격 호출
	DefaultAttack->InvokeSkill();
}

void UPlayerAction::InputSkill(const FInputActionValue& InputValue)
{
	if (Player->CheckPlayerIsDead())
		return;

	int32 Value = (int32)InputValue.Get<float>();
	InvokeSkill(Value);
}

void UPlayerAction::InvokeSkill(int32 InValue)
{
	PRINT_LOG(TEXT("Test Skill Input : %d"), InValue);
}