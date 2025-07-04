// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerAction.h"
#include "Core/TDRPGPlayerController.h"

#include "Character/TDRPGPlayer.h"
#include "Character/TDRPGEnemy.h"
#include "Character/CharacterData.h"
#include "Character/PlayerAnim.h"

#include "TDRPGEnum.h"
#include "Core/GameDataManager.h"
#include "Data/SkillDataRow.h"
#include "Character/Skill/Skill.h"

#include <EnhancedInputComponent.h>
#include <Components/SphereComponent.h>

#include "TopDownRPG/TopDownRPG.h"


UPlayerAction::UPlayerAction(){}

void UPlayerAction::InitializeComponent()
{
	Super::InitializeComponent();

	Player->HitCollider->OnComponentBeginOverlap.AddDynamic(this, &UPlayerAction::OnActorOverlaped);
	ActivateHitCollider(false);
}

void UPlayerAction::SetupInputBinding(UEnhancedInputComponent* PlayerInputComponent, ATDRPGPlayerController* InController)
{
	Super::SetupInputBinding(PlayerInputComponent, InController);

	PlayerInputComponent->BindAction(InController->AttackDefaultAction, ETriggerEvent::Triggered, this, &UPlayerAction::InputAttack);
	PlayerInputComponent->BindAction(InController->SkillAction, ETriggerEvent::Triggered, this, &UPlayerAction::InputSkill);
}

void UPlayerAction::Initialize(TArray<FString>& InSkillIDs)
{
	SkillMap.Empty();

	UGameDataManager* GameData = GetWorld()->GetGameInstance()->GetSubsystem<UGameDataManager>();
	for(FString& ID : InSkillIDs)
	{
		FSkillDataRow* SkillData = GameData->GetRow<FSkillDataRow>(ETableType::Skill, ID);
		check(SkillData);
		
		USkill* Skill;
		
		SkillData->Type == ESkillType::Active ? 
			Skill = NewObject<UActiveSkill>() : 
			Skill = NewObject<UPassiveSkill>();

		Skill->Initialize(*SkillData, GetOwner());

		SkillMap.Add(ID, Skill);

		if (SkillData->bIsDefaultAction)
			DefaultAttack = Cast<UActiveSkill>(Skill);
	}
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

void UPlayerAction::ActivateHitCollider(bool bIsEnable)
{
	Player->HitCollider->SetCollisionEnabled(bIsEnable ? ECollisionEnabled::QueryAndPhysics: ECollisionEnabled::NoCollision);
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


void UPlayerAction::OnActorOverlaped(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	if(OtherActor && OtherActor->IsA<ATDRPGEnemy>())
	{
		ATDRPGEnemy* Enemy = Cast<ATDRPGEnemy>(OtherActor);
		int32 Damage = Player->DataComp->GetAttackPower();

		Enemy->TakeDamage(Damage);
	}
}
