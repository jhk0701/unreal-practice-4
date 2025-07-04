// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/SkillEffectBase.h"

#include <Components/BoxComponent.h>

#include "TopDownRPG/TopDownRPG.h"

ASkillEffectBase::ASkillEffectBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Effect Mesh"));
	SetRootComponent(Mesh);

	if (!Collider)
	{
		Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Default Collider"));
		Collider->SetupAttachment(Mesh);
	}
}

void ASkillEffectBase::BeginPlay()
{
	Super::BeginPlay();

	Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASkillEffectBase::OnBeginOverlapped);
}

void ASkillEffectBase::Initialize(AActor* InActivator)
{
	Activator = InActivator;
}


void ASkillEffectBase::Activate()
{
	SetActive(true);

	auto& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(
		Timer,
		FTimerDelegate::CreateUObject(this, &ASkillEffectBase::Deactivate), 
		LifeTime, 
		false);

	OnSkillStarted.Broadcast(this);
}

void ASkillEffectBase::Deactivate()
{
	OnSkillEnded.Broadcast(this);
	SetActive(false);
}

void ASkillEffectBase::OnBeginOverlapped(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (OtherActor == Owner)
		return;

	OnSkillHitted.Broadcast(this);
}


void ASkillEffectBase::SetActive(bool bIsOn)
{
	SetActorHiddenInGame(bIsOn);
	SetActorEnableCollision(bIsOn);
}

