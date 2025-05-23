// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/NPCMerchant.h"
#include <Components/SphereComponent.h>
#include <Components/CapsuleComponent.h>

#include "TopDownRPG/TopDownRPG.h"

ANPCMerchant::ANPCMerchant()
{
	collider->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	collider->SetGenerateOverlapEvents(false);

	DetectArea = CreateDefaultSubobject<USphereComponent>(TEXT("DetectArea"));
	DetectArea->SetupAttachment(RootComponent);
	DetectArea->InitSphereRadius(300);
	DetectArea->SetGenerateOverlapEvents(true);
	DetectArea->SetCollisionProfileName(TEXT("Interaction"));
}

void ANPCMerchant::BeginPlay()
{
	Super::BeginPlay();

	DetectArea->OnComponentBeginOverlap.AddUniqueDynamic(this, &ANPCMerchant::OnBeginOverlapped);
	DetectArea->OnComponentEndOverlap.AddUniqueDynamic(this, &ANPCMerchant::OnEndOverlapped);
}

void ANPCMerchant::Interact()
{
}

void ANPCMerchant::OnBeginOverlapped(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex,
	bool bFromSweep, 
	const FHitResult& SweepResult
)
{
	PRINT_LOG(TEXT("On Overlap Begin"));
}

void ANPCMerchant::OnEndOverlapped(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex
)
{
	PRINT_LOG(TEXT("On Overlap End"));
}
