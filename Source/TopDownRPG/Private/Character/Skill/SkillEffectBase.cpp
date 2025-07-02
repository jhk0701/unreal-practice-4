// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/SkillEffectBase.h"

#include <Components/SphereComponent.h>


ASkillEffectBase::ASkillEffectBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ASkillEffectBase::BeginPlay()
{
	Super::BeginPlay();

	Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ASkillEffectBase::OnBeginOverlapped);

}

void ASkillEffectBase::Activate()
{
	OnSkillStarted.Broadcast(this);
}

void ASkillEffectBase::OnBeginOverlapped(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{

}

